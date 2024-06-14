//
// Created by 19254 on 24-6-4.
//
#include <map>
#include "HYGUI/Object.h"
#include "HYGUI/Window.h"
#include "HYGUI/Event.h"
#include "PrivateDefinition.h"


namespace HYGUI {


// 组件绘制消息
int _obj_paint(HYWindow *window, HYObject *obj, int event, uint64_t param1, uint32_t param2) {
  for (auto &callback: obj->EventCallbacks) {
    if (callback(obj->Window, obj, HYObjectEvent_Paint, 0, 0) != 0) {
      break;
    }
  }
  if (!obj->Children.empty()) {
    for (auto &child: obj->Children) {
      _obj_paint(window, child, event, param1, param2);
    }
  }
  return 0;
}

// 组件事件_鼠标移动
int _obj_mouse_move(HYWindow *window, HYObject *obj, int event, uint64_t param1, uint32_t param2) {
  auto p = HYPointFromLParam(param2);
  // PrintDebug("obj_mouse_move {} {} {}",obj->Name.toStdStringView(), p.x, p.y);
  return 0;
}

std::map<int, std::function<int(HYWindow *, HYObject *, int, uint64_t, uint32_t)>> _obj_event_callback_map = {
  // 鼠标移动
  {HYObjectEvent_MouseMove, _obj_mouse_move},
  // 组件绘制
  {HYObjectEvent_Paint,     _obj_paint}
};

int _obj_event(HYWindow *window, HYObject *obj, int event, uint64_t param1, uint32_t param2) {
  auto iter = _obj_event_callback_map.find(event);
  if (iter != _obj_event_callback_map.end()) {
    return iter->second(window, obj, event, param1, param2);
  }
  return 0;
}


int processing_object_event(HYObjectEventQueue *queue, HYObjectEventInfo &event_info) {
  _obj_event(event_info.Window, event_info.Object, event_info.Event, event_info.Param1, event_info.Param2);
  return 0;
  // return HYWindowSendEvent(event_info.Window, HYObjectEventTag, (uint64_t) ((void *) (&event_info)), HYObjectEventTag);
}

HYObject::HYObject(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height,
                   const HYString &className, const HYString &name, int id) :
  Window(window), Parent(reinterpret_cast<HYObject *>(parent)), X(x), Y(y), Width(width), Height(height),
  ClassName(className), Name(name), ID(id) {
  if (parent) {
    parent->Children.insert(this);
  } else {
    window->Children.insert(this);
  }
  // HYObjectAddEventCallback(this, _obj_event);
}

HYObjectHandle HYObjectCreate(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height,
                              const HYString &className, const HYString &name, int id) {
  if (!window) {
    return nullptr;
  }
  if (!window->Handle) {
    return nullptr;
  }
  return new HYObject{window, parent, x, y, width, height, className, name, id};
}

void HYObjectPostEvent(HYWindow *window, HYObjectHandle object, int event, uint64_t param1, uint32_t param2) {
  std::lock_guard<std::mutex> lock(window->MessageMutex);
  if (!window->EventQueue.IsRunning()) {
    window->EventQueue.Start();
  }
  HYObjectEventInfo i = {
    (HYObjectEvent) event,
    window,
    object,
    param1,
    param2,
  };
  // 有序发送
  window->EventQueue.Push(i);
}

void HYObjectSendEvent(HYWindow *window, HYObjectHandle object, int event, uint64_t param1, uint32_t param2) {
  std::lock_guard<std::mutex> lock(window->MessageMutex);
  if (!window->EventQueue.IsRunning()) {
    window->EventQueue.Start();
  }
  HYObjectEventInfo i = {
    (HYObjectEvent) event,
    window,
    object,
    param1,
    param2,
  };
  bool wl = true;
  bool isPush = false;
  while (wl) {
    if (!window->EventQueue.Empty()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      continue;
    }
    if (!isPush) {
      window->EventQueue.Push(i);
      isPush = true;
      continue;
    }
    wl = false;
  }
}

void HYObjectRefresh(HYObjectHandle object) {
  if (!object) {
    return;
  }
  HYObjectSendEvent(object->Window, object, HYObjectEvent_Paint, 0, 0);
}

void HYObjectDestroy(HYObjectHandle object) {
  if (object->Parent) {
    object->Parent->Children.erase(object);
  }
  delete object;
}

bool HYObject::contains(int px, int py) const {
  return px >= X && px < (X + Width) && py >= Y && py < (Y + Height);
}

void HYObjectAddEventCallback(HYObjectHandle object, const HYObjectEventCallback &callback) {
  object->EventCallbacks.push_back(callback);
}

void HYObjectUserDataAdd(HYObjectHandle object, intptr_t key, intptr_t data) {
  object->UserData[key] = data;
}

void HYObjectUserDataRemove(HYObjectHandle object, intptr_t key,
                            const std::function<bool(HYObjectHandle object, intptr_t key, intptr_t value)> &callback) {
  if (object->UserData.find(key) != object->UserData.end()) {
    if (!callback || callback(object, key, object->UserData[key])) {
      object->UserData.erase(key);
    }
  }
}

void HYObjectSetClassName(HYObjectHandle object, const HYString &className) {
  object->ClassName = className;
}

void HYObjectSetName(HYObjectHandle object, const HYString &name) {
  object->Name = name;
}

void HYObjectSetID(HYObjectHandle object, int id) {
  object->ID = id;
}

// 递归查找子对象
HYObjectHandle HYObjectObjFromMousePos(HYObjectHandle obj, int px, int py, int offsetX, int offsetY) {
  if (!obj->contains(px - offsetX, py - offsetY)) {
    return nullptr;
  }

  // 更新相对坐标
  offsetX += obj->X;
  offsetY += obj->Y;

  // 从后往前遍历子对象
  for (auto it = obj->Children.rbegin(); it != obj->Children.rend(); ++it) {
    auto found = HYObjectObjFromMousePos(*it, px, py, offsetX, offsetY);
    if (found) {
      return found;
    }
  }

  return obj;
}

HYObjectHandle HYObjectObjFromMousePos(HYWindow *window, int px, int py) {
  HYObjectHandle topObject = nullptr;
  // 从后往前遍历子对象
  for (auto it = window->Children.rbegin(); it != window->Children.rend(); ++it) {
    auto found = HYObjectObjFromMousePos(*it, px, py, 0, 0);
    if (found) {
      topObject = found;
    }
  }
  return topObject;
}

HYPoint HYObjectGetRelativePoint(HYObjectHandle object, int windowX, int windowY) {
  HYPoint raw;
  if (object->Parent) {
    auto tmp = HYObjectGetRelativePoint(object->Parent, windowX, windowY);
    raw.x = tmp.x - object->X;
    raw.y = tmp.y - object->Y;
  } else {
    raw.x = windowX - object->X;
    raw.y = windowY - object->Y;
  }
  return raw;
}

HYRect HYObjectGetNestedClippedVisibleArea(HYObjectHandle object, const HYRect &rect) {
  HYRect raw;
  if (rect.x == 0
      && rect.y == 0
      && rect.width == 0
      && rect.height == 0) {
    raw = {object->X,
           object->Y,
           object->Width, object->Height};
  } else {
    raw = rect;
  }

  if (raw.x < 0) {
    raw.width += raw.x;
    raw.x = 0;
  }
  if (raw.y < 0) {
    raw.height += raw.y;
    raw.y = 0;
  }
  if (object->Parent) {
    // 还有上级父区域
    auto tmp = HYObjectGetNestedClippedVisibleArea(object->Parent);
    if (raw.width > tmp.width) {
      raw.width = tmp.width;
    }
    if (raw.height > tmp.height) {
      raw.height = tmp.height;
    }
    raw.x += tmp.x;
    raw.y += tmp.y;
  }
  return raw;
}

PaintPtr HYObjectBeginPaint(HYObjectHandle object, const HYRect &rect) {
  // 计算实际可视区域
  HYRect lct = HYObjectGetNestedClippedVisibleArea(object, rect);
  // 创建画布
  object->Canvas = object->Window->Canvas;
  object->Canvas->save();
  object->Canvas->translate(lct.x, lct.y);
  object->Canvas->clipRect(SkRect::MakeWH(lct.width, lct.height));
  // PrintDebug("HYObjectBeginPaint {} {} {} {} {}", object->Name.toStdStringView(), lct.x, lct.y, lct.width, lct.height);
  // 创建画笔
  auto repaint = new SkPaint();
  repaint->setAntiAlias(true);

  return repaint;
}


void HYObjectEndPaint(HYObjectHandle object,SkPaint*repaint) {
  object->Canvas->restore();
  object->Canvas = nullptr;
  delete repaint;
}

}
