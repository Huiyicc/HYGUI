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
  // 鼠标右键按下
  HYObjectEvent_RightUp,
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
  HYObjectEvent_CharInput,

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

  template<typename TC>
  uint32_t _registerCallback(std::map<uint32_t,TC>& table, const TC &callback) {
    auto riter = table.rbegin();
    if (riter == table.rend()) {
      table.insert(std::make_pair(0, callback));
      return 0;
    }
    auto id = riter->first + 1;
    table.insert(std::make_pair(id, callback));
    return id;
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

  std::map<uint32_t, HYObjectEventDestroyHandel> EventDestroyCallbacks;
  /**
   * @brief 添加对象销毁回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventDestroyCallback(const HYObjectEventDestroyHandel &callback);
  /**
   * @brief 删除对象销毁回调
   * @param id: 回调ID
   * */
  void UnRegisterEventDestroyCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventPaintHandel> EventPaintCallbacks;
  /**
   * @brief 添加对象重绘回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventPaintCallback(const HYObjectEventPaintHandel &callback);
  /**
   * @brief 删除对象重绘回调
   * @param id: 回调ID
   * */
  void UnRegisterEventPaintCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventResizeHandel> EventResizeCallbacks;
  /**
   * @brief 添加对象大小改变回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventResizeCallback(const HYObjectEventResizeHandel &callback);
  /**
   * @brief 删除对象大小改变回调
   * @param id: 回调ID
   * */
  void UnRegisterEventResizeCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventShowHandel> EventShowCallbacks;
  /**
   * @brief 添加对象被显示回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventShowCallback(const HYObjectEventShowHandel &callback);
  /**
   * @brief 删除对象被显示回调
   * @param id: 回调ID
   * */
  void UnRegisterEventShowCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventHideHandel> EventHideCallbacks;
  /**
   * @brief 添加对象被隐藏回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventHideCallback(const HYObjectEventHideHandel &callback);
  /**
   * @brief 删除对象被隐藏回调
   * @param id: 回调ID
   * */
  void UnRegisterEventHideCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventLeftDownHandel> EventLeftDownCallbacks;
  /**
   * @brief 添加对象鼠标左键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventLeftDownCallback(const HYObjectEventLeftDownHandel &callback);
  /**
   * @brief 删除对象鼠标左键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventLeftDownCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventLeftUpHandel> EventLeftUpCallbacks;
  /**
   * @brief 添加对象鼠标左键放开回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventLeftUpCallback(const HYObjectEventLeftUpHandel &callback);
  /**
   * @brief 删除对象鼠标左键放开回调
   * @param id: 回调ID
   * */
  void UnRegisterEventLeftUpCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventLeftUpHandel> EventRightUpCallbacks;
  /**
   * @brief 添加对象鼠标右键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventRightUpCallback(const HYObjectEventRightUpHandel &callback);
  /**
   * @brief 删除对象鼠标右键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventRightUpCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventRightDownHandel> EventRightDownCallbacks;
  /**
   * @brief 添加对象鼠标右键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventRightDownCallback(const HYObjectEventRightDownHandel &callback);
  /**
   * @brief 删除对象鼠标右键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventRightDownCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventMouseMoveHandel> EventMouseMoveCallbacks;
  /**
   * @brief 添加对象鼠标移动回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseMoveCallback(const HYObjectEventMouseMoveHandel &callback);
  /**
   * @brief 删除对象鼠标移动回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseMoveCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventDoubleClickHandel> EventDoubleClickCallbacks;
  /**
   * @brief 添加对象被双击回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventDoubleClickCallback(const HYObjectEventDoubleClickHandel &callback);
  /**
   * @brief 删除对象被双击回调
   * @param id: 回调ID
   * */
  void UnRegisterEventDoubleClickCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventKeyDownHandel> EventKeyDownCallbacks;
  /**
   * @brief 添加对象按下某键回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventKeyDownCallback(const HYObjectEventKeyDownHandel &callback);
  /**
   * @brief 删除对象按下某键回调
   * @param id: 回调ID
   * */
  void UnRegisterEventKeyDownCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventKeyUpHandel> EventKeyUpCallbacks;
  /**
   * @brief 添加对象放开某键回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventKeyUpCallback(const HYObjectEventKeyUpHandel &callback);
  /**
   * @brief 删除对象放开某键回调
   * @param id: 回调ID
   * */
  void UnRegisterEventKeyUpCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventMouseWheelHandel> EventMouseWheelCallbacks;
  /**
   * @brief 添加对象滚轮被滚动回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseWheelCallback(const HYObjectEventMouseWheelHandel &callback);
  /**
   * @brief 删除对象滚轮被滚动回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseWheelCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventCharInputHandel> EventCharInputCallbacks;
  /**
   * @brief 添加对象字符输入回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventCharInputCallback(const HYObjectEventCharInputHandel &callback);
  /**
   * @brief 删除对象字符输入回调
   * @param id: 回调ID
   * */
  void UnRegisterEventCharInputCallback(uint32_t id);




};

}// namespace HYGUI

#endif//HYGUI_EVENT_H
