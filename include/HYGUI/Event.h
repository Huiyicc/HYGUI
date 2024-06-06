//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_EVENT_H
#define HYGUI_EVENT_H

// #include "HYGUI/Define.h"
#include "HYGUI/HYAsyncQueueProcessor.h"

namespace HYGUI {

struct HYWindow;
struct HYObject;

constexpr int HYObjectEventTag = 233;
enum HYObjectEvent {
  HYObjectEvent_Create, // 对象创建
  HYObjectEvent_Destroy, // 对象销毁
  HYObjectEvent_Paint, // 对象重绘
};

struct HYObjectEventInfo {
  HYObjectEvent Event;
  HYWindow *Window;
  HYObject* Object;
  intptr_t Param1;
  intptr_t Param2;

};

typedef HYAsyncQueueProcessor<HYObjectEventInfo> HYObjectEventQueue;

}

#endif //HYGUI_EVENT_H
