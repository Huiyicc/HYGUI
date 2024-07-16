//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Object.h"
#include "HYGUI/Event.h"
#include "HYGUI/KeyCode.h"
#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include <map>

namespace HYGUI {


// 组件绘制消息
int _obj_paint(HYWindow *window, HYObject *obj, int event, uint64_t param1, uint32_t param2) {
  int r = 0;
  for (auto &callback: obj->EventPaintCallbacks) {
    if (callback.second) {
      r = callback.second(window, obj);
      if (r != 0) {
        break;
      }
    }
  }
  if (r == 0) {
    if (!obj->Children.empty()) {
      for (auto &child: obj->Children) {
        HYObjectSendEvent(window, child, event, param1, param2);
      }
    }
  }
  return r;
}

int _obj_left_down(HYWindow *window, HYObject *obj, int event, uint64_t param1, uint32_t param2) {
  int r = 0;
  auto mode = SDL_GetModState();
  auto [x, y] = HYPointFromLParam(param2);
  for (auto &callback: obj->EventLeftDownCallbacks) {
    if (callback.second) {
      r = callback.second(window, obj, x, y, mode);
      if (r != 0) {
        break;
      }
    }
  }
  return r;
}

// 组件事件_鼠标移动
int _obj_mouse_move(HYWindow *window, HYObject *obj, int event, uint64_t param1, uint32_t param2) {
  auto p = HYPointFromLParam(param2);
  // PrintDebug("obj_mouse_move {} {} {}", obj->Name.toStdStringView(), p.x, p.y);
  return 0;
}

std::map<int, std::function<int(HYWindow *, HYObject *, int, uint64_t, uint32_t)>> _obj_event_callback_map = {
  // 鼠标移动
  {HYObjectEvent_MouseMove, _obj_mouse_move},
  // 组件绘制
  {HYObjectEvent_Paint, _obj_paint},
  // 鼠标左键被按下
  {HYObjectEvent_LeftDown, _obj_left_down},

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
}

HYObject::HYObject(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height,
                   const HYString &className, const HYString &name, int id) : Window(window), Parent(reinterpret_cast<HYObject *>(parent)), X(x), Y(y), Width(width), Height(height),
                                                                              ClassName(std::make_shared<HYString>(className)), Name(std::make_shared<HYString>(name)), ID(id) {
  RawObjRect = {x, y, width, height};
  if (parent) {
    parent->Children.insert(this);
    if (x < 0) {
      VisibleRect.x = parent->VisibleRect.x;
      VisibleRect.width = x + width;

    } else {
      VisibleRect.x = parent->VisibleRect.x + x;
      VisibleRect.width = width;
    }
    if (y < 0) {
      VisibleRect.y = parent->VisibleRect.y;
      VisibleRect.height = y + height;
    } else {
      VisibleRect.y = parent->VisibleRect.y + y;
      VisibleRect.height = height;
    }
    VisibleRect.width = std::max(0, VisibleRect.width);
    VisibleRect.height = std::max(0, VisibleRect.height);
    if (VisibleRect.width > parent->Width) {
      VisibleRect.width = parent->Width;
    }
    if (VisibleRect.height > parent->Height) {
      VisibleRect.height = parent->Height;
    }
    RawObjRect.x = parent->VisibleRect.x + x;
    RawObjRect.y = parent->VisibleRect.y + y;

  } else {
    window->Children.insert(this);
    if (x < 0) {
      VisibleRect.x = 0;
      VisibleRect.width = x + width;
    } else {
      VisibleRect.x = x;
      VisibleRect.width = width;
    }
    if (y < 0) {
      VisibleRect.y = 0;
      VisibleRect.height = y + height;
    } else {
      VisibleRect.y = y;
      VisibleRect.height = height;
    }
    VisibleRect.width = std::max(0, VisibleRect.width);
    VisibleRect.height = std::max(0, VisibleRect.height);
    if (VisibleRect.width > window->Width) {
      VisibleRect.width = window->Width;
    }
    if (VisibleRect.height > window->Height) {
      VisibleRect.height = window->Height;
    }
  }
  HYResourceRegister(ResourceType::ResourceType_Object, this, className, nullptr);
  // 创建事件
  for (auto &callback: EventCreateCallbacks) {
    if (callback.second) {
      callback.second(window, this);
    }
  }
}

HYObject::~HYObject() {
  for (auto &child: Children) {
    HYResourceRemove(ResourceType::ResourceType_Object, child);
  }
  Children.clear();
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

void HYObjectSendEvent(HYWindow *window, HYObjectHandle object, int event, uint64_t param1, uint32_t param2) {
  _obj_event(window, object, event, param1, param2);
}

void HYObjectSendEventLIst(HYWindow *window, int event, uint64_t param1, uint32_t param2) {
  for (auto &obj: window->Children) {
    _obj_event(window, obj, event, param1, param2);
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
  HYResourceRemove(ResourceType::ResourceType_Object, object);
}

bool HYObject::contains(int px, int py) const {
  return px >= X && px < (X + Width) && py >= Y && py < (Y + Height);
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
  *object->ClassName = className;
}

void HYObjectSetName(HYObjectHandle object, const char *name) {
  *object->Name = name;
}

void HYObjectSetID(HYObjectHandle object, int id) {
  object->ID = id;
}


HYObjectHandle HYObjectGetFromMousePos(HYObjectHandle obj, int px, int py) {
  HYObjectHandle topObject = nullptr;
  for (auto it = obj->Children.rbegin(); it != obj->Children.rend(); ++it) {
    topObject = HYObjectGetFromMousePos(*it, px, py);
    if (topObject) {
      return topObject;
    }
  }
  // 没有子组件命中
  return HYPointIsInsideRectangle({px, py}, obj->VisibleRect) ? obj : nullptr;
}

HYObjectHandle HYObjectGetFromMousePos(HYWindow *window, int px, int py) {
  HYObjectHandle topObject = nullptr;
  for (auto it = window->Children.rbegin(); it != window->Children.rend(); ++it) {
    topObject = HYObjectGetFromMousePos(*it, px, py);
    if (topObject) {
      break;
    }
  }
  return topObject;
}

HYPoint HYObjectGetRelativePoint(HYObjectHandle object, int windowX, int windowY) {
  return {
    windowX - object->RawObjRect.x,
    windowY - object->RawObjRect.y};
}

HYRect HYObjectGetNestedClippedVisibleArea(HYObjectHandle object) {
  return object->VisibleRect;
}

PaintPtr HYObjectBeginPaint(HYObjectHandle object, bool clear) {
  object->Window->PaintMutex.lock();
  // 计算实际可视区域
  HYRect lct = HYObjectGetNestedClippedVisibleArea(object);
  // 创建画布
  object->Canvas = object->Window->Canvas;
  object->Canvas->save();
  //  if (object->Window->GlobalClipPath) {
  //    object->Canvas->clipPath(*object->Window->GlobalClipPath);
  //  }
  object->Canvas->clipRect(SkRect::MakeLTRB(lct.x, lct.y, lct.x + lct.width, lct.y + lct.height));
  object->Canvas->translate(object->RawObjRect.x, object->RawObjRect.y);
  // PrintDebug("HYObjectBeginPaint {} {} {} {} {}", object->Name.toStdStringView(), lct.x, lct.y, lct.width, lct.height);
  // 创建画笔
  auto repaint = new SkPaint();
  repaint->setAntiAlias(true);
  if (clear) {
    // 清除背景
    repaint->setColor(SK_ColorTRANSPARENT);
    object->Canvas->drawRect(SkRect::MakeLTRB(0, 0, object->Width, object->Height), *repaint);
    // 重置画笔
    repaint->setColor(SK_ColorBLACK);
  }
  return repaint;
}


void HYObjectEndPaint(HYObjectHandle object, SkPaint *repaint) {
  object->Canvas->restore();
  object->Canvas = nullptr;
  delete repaint;
  object->Window->PaintMutex.unlock();
}

}// namespace HYGUI
