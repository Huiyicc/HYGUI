//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Object.h"
#include "HYGUI/Window.h"
#include "HYGUI/Event.h"
#include "PrivateDefinition.h"


namespace HYGUI {

//void printCanvasMatrix(const SkCanvas *canvas) {
//  SkM44 localToDevice = canvas->getLocalToDevice();
//  SkMatrix matrix = localToDevice.asM33();
//
//  SkScalar values[9];
//  matrix.get9(values);
//
//  std::cout << "Current Matrix:\n"
//   << "[ 缩放X, 倾斜X, 平移X ] [" << values[0] << ", " << values[1] << ", " << values[2] << "]\n"
//   << "[ 倾斜Y, 缩放Y, 平移Y ] [" << values[3] << ", " << values[4] << ", " << values[5] << "]\n"
//  << "[ 透视0, 透视1, 透视2 ] [" << values[6] << ", " << values[7] << ", " << values[8] << "]" << std::endl;
//}

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

int processing_object_event(HYObjectEventQueue *queue, HYObjectEventInfo &event_info) {
  HYWindowSendEvent(event_info.Window, 0, (intptr_t)((void *) (&event_info)), HYObjectEventTag);
  return 0;
}

HYObject::HYObject(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height) {
  X = x;
  Y = y;
  Width = width;
  Height = height;
  Parent = parent;
  Window = window;
  if (parent) {
    parent->Children.insert(this);
  } else {
    window->Children.insert(this);
  }
}

HYObjectHandle HYObjectCreate(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height) {
  if (!window) {
    return nullptr;
  }
  if (!window->Handle) {
    return nullptr;
  }
  return new HYObject{window, parent, x, y, width, height};
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
  HYObjectSendEvent(object->Window, object, HYObjectEvent_Paint, 0, 0);
}

void HYObjectDestroy(HYObjectHandle object) {
  if (object->Parent) {
    object->Parent->Children.erase(object);
  }
  delete object;
}


void HYObjectAddEventCallback(HYObjectHandle object, const HYObjectEventCallback &callback) {
  object->EventCallbacks.push_back(callback);
}

void HYObjectSetUserData(HYObjectHandle object, intptr_t key, void *data) {
  object->UserData[key] = data;
}

}
