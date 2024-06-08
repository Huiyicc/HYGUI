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

void HYObjectSetUserData(HYObjectHandle object, intptr_t key, void *data) {
  object->UserData[key] = data;
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

  for (HYObjectHandle child : obj->Children) {
    auto found = HYObjectObjFromMousePos(child, px, py, offsetX, offsetY);
    if (found) {
      return found;
    }
  }

  return obj;
}

HYObjectHandle HYObjectObjFromMousePos(HYWindow *window, int px, int py) {
  HYObjectHandle topObject = nullptr;

  for (HYObjectHandle obj : window->Children) {
    auto found = HYObjectObjFromMousePos(obj, px, py, 0, 0);
    if (found) {
      topObject = found;
    }
  }

  return topObject;

//  for (auto &obj: window->Children) {
//    // 检查目标坐标是否在当前对象范围内
//    if (px >= obj->X && px < obj->X + obj->Width &&
//      py >= obj->Y && py < obj->Y + obj->Height) {
//      // 如果当前对象有子对象，继续在子对象中查找
//      if (!obj->Children.empty()) {
//        auto result = HYObjectObjFromMousePos(obj->Window, px - obj->X, py - obj->Y);
//        if (result != nullptr) {
//          return result; // 找到了更深层的匹配对象
//        } else {
//          return obj; // 当前对象没有子对象且坐标在其范围内，即为最上层匹配对象
//        }
//      } else {
//        // 当前对象没有子对象且坐标在其范围内，即为最上层匹配对象
//        return obj;
//      }
//    }
//  }
//  // 如果遍历完所有子对象都没找到匹配的，返回nullptr
//  return nullptr;
}

}
