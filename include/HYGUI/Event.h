//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_EVENT_H
#define HYGUI_EVENT_H

#include "HYGUI/HYAsyncQueueProcessor.h"
#include <map>

namespace HYGUI {

class HYWindow;
struct HYRect;
class HYObject;

constexpr int HYObjectEventTag = 233;

/**
 * @brief 对象事件
 * */
enum HYObjectEvent {
  // ...
  // 预留事件
  // ...

  // 对象创建
  HYObjectEvent_Create = 100,
  // 对象销毁
  HYObjectEvent_Destroy,
  // 对象重绘
  HYObjectEvent_Paint,

  // 尺寸被改变
  HYObjectEvent_Resize,
  // 被显示
  HYObjectEvent_Show,
  // 被隐藏
  HYObjectEvent_Hide,
  // 鼠标左键按下
  HYObjectEvent_LeftDown,
  // 鼠标左键放开
  HYObjectEvent_LeftUp,
  // 鼠标右键按下
  HYObjectEvent_RightDown,
  // 鼠标移动
  HYObjectEvent_MouseMove,
  // 被双击
  HYObjectEvent_DoubleClick,
  // 按下某键
  HYObjectEvent_KeyDown,
  // 放开某键
  HYObjectEvent_KeyUp,
  // 滚轮被滚动
  HYObjectEvent_MouseWheel,
  // 字符输入
  HYObjectEvent_Input,

};

enum HYWindowEvent {
  // ...
  // 预留事件
  // ...
  HYWindowEvent_Create = 100,// 窗口创建
  HYWindowEvent_Destroy,     // 窗口销毁
  HYWindowEvent_Paint,       // 窗口重绘
  HYWindowEvent_MouseMove,   // 鼠标移动
};

struct HYObjectEventInfo {
  HYObjectEvent Event;
  HYWindow *Window;
  HYObject *Object;
  uint64_t Param1;
  uint32_t Param2;
};

typedef HYAsyncQueueProcessor<HYObjectEventInfo> HYObjectEventQueue;

}// namespace HYGUI

#include "EventObjectCallback.h"

namespace HYGUI {


class HYEventBase {
private:
  template<typename T>
  void _unRegisterCallback(T &table, uint32_t id) {
    auto iter = table.find(id);
    if (iter != table.end()) {
      table.erase(iter);
    }
  }

public:
  virtual ~HYEventBase() = default;

  std::map<uint32_t, HYObjectEventCreateHandel> EventCreateCallbacks;
  /**
   * @brief 添加对象创建回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventCreateCallback(const HYObjectEventCreateHandel &callback);
  /**
   * @brief 删除对象创建回调
   * @param id: 回调ID
   * */
  void UnRegisterEventCreateCallback(uint32_t id);


};

}// namespace HYGUI

#endif//HYGUI_EVENT_H
