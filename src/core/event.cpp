//
// Created by 19254 on 24-7-15.
//
#include "HYGUI/Event.h"

namespace HYGUI {

uint32_t HYEventBase::RegisterEventCreateCallback(const HYObjectEventCreateHandel &callback) {
  auto riter = EventCreateCallbacks.rbegin();
  if (riter == EventCreateCallbacks.rend()) {
    EventCreateCallbacks.insert(std::make_pair(0, callback));
    return 0;
  }
  auto id = riter->first + 1;
  EventCreateCallbacks.insert(std::make_pair(id, callback));
  return id;
}

void HYEventBase::UnRegisterEventCreateCallback(uint32_t id) {
  _unRegisterCallback(EventCreateCallbacks,id);
}

}// namespace HYGUI
