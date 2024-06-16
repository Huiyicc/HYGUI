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
  // ...
  // 预留事件
  // ...
  HYObjectEvent_Create = 100, // 对象创建
  HYObjectEvent_Destroy, // 对象销毁
  HYObjectEvent_Paint, // 对象重绘
  HYObjectEvent_MouseMove, // 鼠标移动
};

enum HYWindowEvent {
  // ...
  // 预留事件
  // ...
  HYWindowEvent_Create = 100, // 窗口创建
  HYWindowEvent_Destroy, // 窗口销毁
  HYWindowEvent_Paint, // 窗口重绘
  HYWindowEvent_MouseMove, // 鼠标移动
};

struct HYObjectEventInfo {
  HYObjectEvent Event;
  HYWindow *Window;
  HYObject* Object;
  uint64_t Param1;
  uint32_t Param2;
};

typedef HYAsyncQueueProcessor<HYObjectEventInfo> HYObjectEventQueue;

}

#endif //HYGUI_EVENT_H
