//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Object.h"
#include "HYGUI/Window.h"
#include "HYGUI/Event.h"
#include "PrivateDefinition.h"


namespace HYGUI {

// 组件绘制消息
int _obj_paint(HYObject *obj, SkCanvas *canvas, SkPaint &paint, const HYRect &offset_point) {
  canvas->save();
  canvas->translate(offset_point.x, offset_point.y);
  canvas->clipRect(SkRect::MakeWH(offset_point.width, offset_point.height));
  // printCanvasMatrix(canvas);
  obj->Canvas = canvas;
  obj->Paint = &paint;
  for (auto &callback: obj->EventCallbacks) {
    if (callback(obj->Window, obj, HYObjectEvent_Paint, 0, 0) != 0) {
      break;
    }
  }
  obj->Canvas = nullptr;
  obj->Paint = nullptr;
  canvas->restore();
  for (auto &child: obj->Children) {
    if (_obj_paint(child, canvas, paint,
                   {
                     offset_point.x + child->X,
                     offset_point.y + child->Y,
                     obj->Width - child->X,
                     obj->Height - child->Y
                   }) != 0) {
      break;
    }
    canvas->restore();
  }

  return 0;
}

// 组件事件_鼠标移动
int _obj_mouse_move(HYObject *obj, int x, int y) {
  return 0;
}

int processing_object_event(HYObjectEventQueue *queue, HYObjectEventInfo &event_info) {
  HYWindowSendEvent(event_info.Window, 0, (intptr_t) ((void *) (&event_info)), HYObjectEventTag);
  return 0;
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

void HYObjectSendEvent(HYWindow *window, HYObjectHandle object, int event, intptr_t param1, intptr_t param2) {
  window->EventQueue.Push({
                            (HYObjectEvent) event,
                            window,
                            object,
                            param1,
                            param2,
                          });
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

}
