//
// Created by 19254 on 24-7-28.
//

#ifndef HYGUI_EVENTOBJECT_H
#define HYGUI_EVENTOBJECT_H

#include "Keyboard.h"

namespace HYGUI {

class HYWindow;
class HYObject;
struct HYPoint;
struct HYRect;

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
  // 位置被改变
  HYObjectEvent_Move,
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
  // 鼠标中键按下
  HYObjectEvent_MiddleDown,
  // 鼠标中键放开
  HYObjectEvent_MiddleUp,
  // 鼠标移动
  HYObjectEvent_MouseMove,
  // 鼠标进入组件
  HYObjectEvent_MouseEnter,
  // 鼠标离开组件
  HYObjectEvent_MouseLeave,
  // 按下某键
  HYObjectEvent_KeyDown,
  // 放开某键
  HYObjectEvent_KeyUp,
  // 滚轮被滚动
  HYObjectEvent_MouseWheel,
  // 字符输入
  HYObjectEvent_CharInput,
  // 获取焦点
  HYObjectEvent_FocusGained,
  // 失去焦点
  HYObjectEvent_FocusLost,
};

struct HYObjectEventInfo {
  HYObjectEvent Event;
  HYWindow *Window;
  HYObject *Object;
  uint64_t Param1;
  uint32_t Param2;
};

typedef HYAsyncQueueProcessor<HYObjectEventInfo> HYObjectEventQueue;

/**
 * @brief 组件事件_消息事件
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param HYObjectEvent: 事件类型,参考枚举值HYObjectEvent
 * @param uint64_t: 参数1
 * @param uint32_t: 参数2
 * */
typedef std::function<int(HYWindow *, HYObject *, HYObjectEvent, uint64_t, uint32_t)> HYObjectEventMessageHandel;

/**
 * @brief 组件事件_创建
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYObject *)> HYObjectEventCreateHandel;

/**
 * @brief 组件事件_销毁
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYObject *)> HYObjectEventDestroyHandel;

/**
 * @brief 组件事件_绘制
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *)> HYObjectEventPaintHandel;

/**
 * @brief 组件事件_位置改变
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param HYPoint*: 新位置
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, HYPoint *)> HYObjectEventMoveHandel;

/**
 * @brief 组件事件_尺寸改变
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param HYRect*: 新尺寸
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, HYRect *)> HYObjectEventResizeHandel;

/**
 * @brief 组件事件_显示
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYObject *)> HYObjectEventShowHandel;

/**
 * @brief 组件事件_隐藏
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYObject *)> HYObjectEventHideHandel;

/**
 * @brief 组件事件_鼠标左键按下
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventLeftDownHandel;

/**
 * @brief 组件事件_鼠标左键放开
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventLeftUpHandel;

/**
 * @brief 组件事件_鼠标右键放开
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventRightUpHandel;

/**
 * @brief 组件事件_鼠标右键按下
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventRightDownHandel;

/**
 * @brief 组件事件_鼠标中键放开
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventMiddleUpHandel;

/**
 * @brief 组件事件_鼠标中键按下
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventMiddleDownHandel;

/**
 * @brief 组件事件_鼠标移动
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, HYKeymod)> HYObjectEventMouseMoveHandel;

/**
 * @brief 组件事件_鼠标进入
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *)> HYObjectEventMouseEnterHandel;

/**
 * @brief 组件事件_鼠标退出
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *)> HYObjectEventMouseLeaveHandel;

/**
 * @brief 组件事件_按下某键
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param HYKeyboardID: 键盘ID
 * @param HYScancode: 键盘扫描键值 HY_SCANCODE_
 * @param HYKeyCode: 键盘键值 HY_KEY_
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod)> HYObjectEventKeyDownHandel;

/**
 * @brief 组件事件_放开某键
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param HYKeyboardID: 键盘ID
 * @param HYScancode: 键盘扫描键值 HY_SCANCODE_
 * @param HYKeyCode: 键盘键值 HY_KEY_
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod)> HYObjectEventKeyUpHandel;

/**
 * @brief 组件事件_滚轮被滚动
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param float: x滚动距离
 * @param float: y滚动距离(一般只需要关注y)
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, float, float, HYKeymod)> HYObjectEventMouseWheelHandel;

/**
 * @brief 组件事件_字符输入
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param HYKeyCode: 字符码
 * @param HYKeymod: 保留参数
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, HYKeyCode, HYKeymod)> HYObjectEventCharInputHandel;

/**
 * @brief 组件事件_获取焦点
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYObject *)> HYObjectEventFocusGainedHandel;

/**
 * @brief 组件事件_丢失焦点
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYObject *)> HYObjectEventFocusLostHandel;


class HYObjectEventBase {
private:
  template<typename T>
  void _unRegisterCallback(T &table, uint32_t id) {
    auto iter = table.find(id);
    if (iter != table.end()) {
      table.erase(iter);
    }
  }

  template<typename TC>
  uint32_t _registerCallback(std::map<uint32_t, TC> &table, const TC &callback) {
    if (!callback) {
      return 0;
    }
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
  virtual ~HYObjectEventBase() = default;

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

  std::map<uint32_t, HYObjectEventMoveHandel> EventMoveCallbacks;
  /**
   * @brief 添加对象位置改变回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMoveCallback(const HYObjectEventMoveHandel &callback);
  /**
   * @brief 删除对象位置改变回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMoveCallback(uint32_t id);

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
   * @brief 添加对象鼠标中键弹起回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventRightUpCallback(const HYObjectEventRightUpHandel &callback);
  /**
   * @brief 删除对象鼠标中键弹起回调
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


  std::map<uint32_t, HYObjectEventMiddleUpHandel> EventMiddleUpCallbacks;
  /**
   * @brief 添加对象鼠标右键弹起回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMiddleUpCallback(const HYObjectEventMiddleUpHandel &callback);
  /**
   * @brief 删除对象鼠标右键弹起回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMiddleUpCallback(uint32_t id);

  std::map<uint32_t, HYObjectEventMiddleDownHandel> EventMiddleDownCallbacks;
  /**
   * @brief 添加对象鼠标中键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMiddleDownCallback(const HYObjectEventMiddleDownHandel &callback);
  /**
   * @brief 删除对象鼠标中键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMiddleDownCallback(uint32_t id);

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


  std::map<uint32_t, HYObjectEventMouseEnterHandel> EventMouseEnterCallbacks;
  /**
   * @brief 添加鼠标进入回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseEnterCallback(const HYObjectEventMouseEnterHandel &callback);
  /**
   * @brief 删除鼠标退出回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseEnterCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventMouseLeaveHandel> EventMouseLeaveCallbacks;
  /**
   * @brief 添加鼠标进入回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseLeaveCallback(const HYObjectEventMouseLeaveHandel &callback);
  /**
   * @brief 删除鼠标退出回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseLeaveCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventFocusGainedHandel> EventFocusGainedCallbacks;
  /**
   * @brief 添加获取焦点回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventFocusGainedCallback(const HYObjectEventFocusGainedHandel &callback);
  /**
   * @brief 删除获取焦点回调
   * @param id: 回调ID
   * */
  void UnRegisterEventFocusGainedCallback(uint32_t id);


  std::map<uint32_t, HYObjectEventFocusLostHandel> EventFocusLostCallbacks;
  /**
   * @brief 添加丢失焦点回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventFocusLostCallback(const HYObjectEventFocusLostHandel &callback);
  /**
   * @brief 删除丢失焦点回调
   * @param id: 回调ID
   * */
  void UnRegisterEventFocusLostCallback(uint32_t id);


};


}

#endif//HYGUI_EVENTOBJECT_H
