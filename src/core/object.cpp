//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Object.h"
#include "HYGUI/Window.h"
#include "HYGUI/Event.h"
#include "PrivateDefinition.h"


namespace HYGUI {

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
                            .Event = (HYObjectEvent) event,
                            .Window = window,
                            .Object = object,
                            .Param1 = param1,
                            .Param2 = param2,
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
