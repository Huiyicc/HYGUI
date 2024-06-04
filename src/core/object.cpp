//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Object.h"
#include "HYGUI/Window.h"

namespace HYGUI {

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

void HYObjectDestroy(HYObjectHandle object) {
  if (object->Parent) {
    object->Parent->Children.erase(object);
  }
  delete object;
}

int HYObjectSendEvent(HYObjectHandle object, int event, int param1, int param2) {
  for (auto &callback: object->EventCallbacks) {
    if (callback(object->Window, object, event, param1, param2) != 0) {
      return 1;
    }
  }
  return 0;
}

void HYObjectAddEventCallback(HYObjectHandle object, const HYObjectEventCallback &callback) {
  object->EventCallbacks.push_back(callback);
}

}
