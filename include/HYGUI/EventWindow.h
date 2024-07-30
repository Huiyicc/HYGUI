//
// Created by 19254 on 24-7-28.
//

#ifndef HYGUI_EVENTWINDOW_H
#define HYGUI_EVENTWINDOW_H

#include "Keyboard.h"
#include "Define.h"

namespace HYGUI {

class HYWindow;
struct HYPoint;
struct HYRect;

enum HYWindowEvent {
  // ...
  // 预留事件
  // ...

  // 窗口创建完毕
  HYWindowEvent_Create = 100,
  // 窗口背景重绘
  HYWindowEvent_BackgroundPaint,
  // 窗口刷新
  HYWindowEvent_Refresh,
  // 窗口可否被关闭
  HYWindowEvent_BeforeClose,
  // 窗口即将销毁
  HYWindowEvent_WillDestroy,
  // 窗口位置被改变
  HYWindowEvent_Move,
  // 窗口尺寸被改变
  HYWindowEvent_Resize,
  // 窗口被激活
  HYWindowEvent_Activate,
  // 窗口被取消激活
  HYWindowEvent_Deactivate,
  // 窗口空闲
  HYWindowEvent_Idle,
  // 窗口首次激活
  HYWindowEvent_FirstActivate,
  // 托盘事件
  HYWindowEvent_Tray,
  // 被显示
  HYWindowEvent_Show,
  // 被隐藏
  HYWindowEvent_Hide,
  // 鼠标左键按下
  HYWindowEvent_LeftDown,
  // 鼠标左键放开
  HYWindowEvent_LeftUp,
  // 鼠标右键按下
  HYWindowEvent_RightDown,
  // 鼠标右键按下
  HYWindowEvent_RightUp,
  // 鼠标中键按下
  HYWindowEvent_MiddleDown,
  // 鼠标中键放开
  HYWindowEvent_MiddleUp,
  // 鼠标移动
  HYWindowEvent_MouseMove,
  // 鼠标进入组件
  HYWindowEvent_MouseEnter,
  // 鼠标离开组件
  HYWindowEvent_MouseLeave,
  // 按下某键
  HYWindowEvent_KeyDown,
  // 放开某键
  HYWindowEvent_KeyUp,
  // 滚轮被滚动
  HYWindowEvent_MouseWheel,
  // 字符输入
  HYWindowEvent_CharInput,
  // 获取焦点
  HYWindowEvent_FocusGained,
  // 失去焦点
  HYWindowEvent_FocusLost,

};

struct HYWindowEventInfo {
  HYWindowEvent Event;
  HYWindow *Window;
  uint64_t Param1;
  uint32_t Param2;
};


/**
 * @brief 窗口事件_创建完毕
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventCreateHandel;

/**
 * @brief 窗口事件_背景重绘
 * @param HYWindow*: 窗口句柄
 * @param CanvasPtr: 背景画布指针
 * @param PaintPtr: 背景画笔指针
 * @param HYRect*: 背景区域
 * */
typedef std::function<void(HYWindow *,CanvasPtr ,PaintPtr, HYRect*)> HYWindowEventBackgroundPaintHandel;

/**
 * @brief 窗口事件_刷新
 * @param HYWindow*: 窗口句柄
 * @param PaintPtr: 背景画笔指针
 * @param HYRect*: 背景区域
 * */
typedef std::function<void(HYWindow *)> HYWindowEventRefreshHandel;

/**
 * @brief 窗口事件_可否被关闭
 *
 * 返回true: 拦截, false: 放行
 *
 * @param HYWindow*: 窗口句柄
 * @result bool: 是否可被关闭
 * */
typedef std::function<bool(HYWindow *)> HYWindowEventBeforeCloseHandel;

/**
 * @brief 窗口事件_即将销毁
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventWillDestroyHandel;

/**
 * @brief 窗口事件_位置改变
 * @param HYWindow*: 窗口句柄
 * @param HYPoint*: 新尺寸
 * */
typedef std::function<void(HYWindow *, HYPoint *)> HYWindowEventMoveHandel;

/**
 * @brief 窗口事件_尺寸改变
 * @param HYWindow*: 窗口句柄
 * @param HYRect*: 新尺寸
 * */
typedef std::function<void(HYWindow *, HYRect *)> HYWindowEventResizeHandel;

/**
 * @brief 窗口事件_首次激活
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventFirstActivateHandel;

/**
 * @brief 窗口事件_托盘事件
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventTrayHandel;

/**
 * @brief 窗口事件_被显示
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventShowHandel;

/**
 * @brief 窗口事件_被隐藏
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventHideHandel;

/**
 * @brief 窗口事件_鼠标左键按下
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventLeftDownHandel;

/**
 * @brief 窗口事件_鼠标左键放开
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventLeftUpHandel;

/**
 * @brief 窗口事件_鼠标右键放开
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventRightUpHandel;

/**
 * @brief 窗口事件_鼠标右键按下
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventRightDownHandel;

/**
 * @brief 窗口事件_鼠标中键放开
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventMiddleUpHandel;

/**
 * @brief 窗口事件_鼠标中键按下
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventMiddleDownHandel;

/**
 * @brief 窗口事件_鼠标移动
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventMouseMoveHandel;

/**
 * @brief 窗口事件_鼠标进入
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventMouseEnterHandel;

/**
 * @brief 窗口事件_鼠标退出
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventMouseLeaveHandel;

/**
 * @brief 窗口事件_按下某键
 * @param HYWindow*: 窗口句柄
 * @param HYKeyboardID: 键盘ID
 * @param HYScancode: 键盘扫描键值 HY_SCANCODE_
 * @param HYKeyCode: 键盘键值 HY_KEY_
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod)> HYWindowEventKeyDownHandel;

/**
 * @brief 窗口事件_放开某键
 * @param HYWindow*: 窗口句柄
 * @param HYKeyboardID: 键盘ID
 * @param HYScancode: 键盘扫描键值 HY_SCANCODE_
 * @param HYKeyCode: 键盘键值 HY_KEY_
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod)> HYWindowEventKeyUpHandel;

/**
 * @brief 窗口事件_滚轮被滚动
 * @param HYWindow*: 窗口句柄
 * @param float: x滚动距离
 * @param float: y滚动距离(一般只需要关注y)
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, float, float, HYKeymod)> HYWindowEventMouseWheelHandel;

/**
 * @brief 窗口事件_字符输入
 * @param HYWindow*: 窗口句柄
 * @param HYKeyCode: 字符码
 * @param HYKeymod: 保留参数
 * */
typedef std::function<void(HYWindow *, HYKeyCode, HYKeymod)> HYWindowEventCharInputHandel;

/**
 * @brief 窗口事件_获取焦点
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventFocusGainedHandel;

/**
 * @brief 窗口事件_丢失焦点
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventFocusLostHandel;


class HYWindowEventBase {
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
  virtual ~HYWindowEventBase() = default;

  std::map<uint32_t, HYWindowEventCreateHandel> EventCreateCallbacks;
  /**
   * @brief 添加窗口创建完毕回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventCreateCallback(const HYWindowEventCreateHandel &callback);
  /**
   * @brief 删除窗口创建完毕回调
   * @param id: 回调ID
   * */
  void UnRegisterEventCreateCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventBackgroundPaintHandel> EventBackgroundPaintCallbacks;
  /**
   * @brief 添加窗口创建完毕回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventBackgroundPaintCallback(const HYWindowEventBackgroundPaintHandel &callback);
  /**
   * @brief 删除窗口创建完毕回调
   * @param id: 回调ID
   * */
  void UnRegisterEventBackgroundPaintCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventRefreshHandel> EventRefreshCallbacks;
  /**
   * @brief 添加窗口刷新回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventRefreshCallback(const HYWindowEventRefreshHandel &callback);
  /**
   * @brief 删除窗口刷新回调
   * @param id: 回调ID
   * */
  void UnRegisterEventRefreshCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventBeforeCloseHandel> EventBeforeCloseCallbacks;
  /**
   * @brief 添加窗口可否被关闭回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventBeforeCloseCallback(const HYWindowEventBeforeCloseHandel &callback);
  /**
   * @brief 删除窗口销毁回调
   * @param id: 回调ID
   * */
  void UnRegisterEventBeforeCloseCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventWillDestroyHandel> EventWillDestroyCallbacks;
  /**
   * @brief 添加窗口即将销毁回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventWillDestroyCallback(const HYWindowEventWillDestroyHandel &callback);
  /**
   * @brief 删除窗口即将销毁回调
   * @param id: 回调ID
   * */
  void UnRegisterEventWillDestroyCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventMoveHandel> EventMoveCallbacks;
  /**
   * @brief 添加窗口位置改变回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMoveCallback(const HYWindowEventMoveHandel &callback);
  /**
   * @brief 删除窗口位置改变回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMoveCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventResizeHandel> EventResizeCallbacks;
  /**
   * @brief 添加窗口大小改变回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventResizeCallback(const HYWindowEventResizeHandel &callback);
  /**
   * @brief 删除窗口大小改变回调
   * @param id: 回调ID
   * */
  void UnRegisterEventResizeCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventFirstActivateHandel> EventFirstActivateCallbacks;
  /**
   * @brief 添加窗口首次激活回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventFirstActivateCallback(const HYWindowEventFirstActivateHandel &callback);
  /**
   * @brief 删除窗口首次激活回调
   * @param id: 回调ID
   * */
  void UnRegisterEventFirstActivateCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventTrayHandel> EventTrayCallbacks;
  /**
   * @brief 添加窗口托盘事件回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventTrayCallback(const HYWindowEventTrayHandel &callback);
  /**
   * @brief 删除窗口托盘事件回调
   * @param id: 回调ID
   * */
  void UnRegisterEventTrayCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventShowHandel> EventShowCallbacks;
  /**
   * @brief 添加窗口被显示回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventShowCallback(const HYWindowEventShowHandel &callback);
  /**
   * @brief 删除窗口被显示回调
   * @param id: 回调ID
   * */
  void UnRegisterEventShowCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventHideHandel> EventHideCallbacks;
  /**
   * @brief 添加窗口被隐藏回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventHideCallback(const HYWindowEventHideHandel &callback);
  /**
   * @brief 删除窗口被隐藏回调
   * @param id: 回调ID
   * */
  void UnRegisterEventHideCallback(uint32_t id);



  std::map<uint32_t, HYWindowEventLeftDownHandel> EventLeftDownCallbacks;
  /**
   * @brief 添加窗口鼠标左键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventLeftDownCallback(const HYWindowEventLeftDownHandel &callback);
  /**
   * @brief 删除窗口鼠标左键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventLeftDownCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventLeftUpHandel> EventLeftUpCallbacks;
  /**
   * @brief 添加窗口鼠标左键放开回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventLeftUpCallback(const HYWindowEventLeftUpHandel &callback);
  /**
   * @brief 删除窗口鼠标左键放开回调
   * @param id: 回调ID
   * */
  void UnRegisterEventLeftUpCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventMiddleUpHandel> EventMiddleUpCallbacks;
  /**
   * @brief 添加窗口鼠标右键弹起回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMiddleUpCallback(const HYWindowEventMiddleUpHandel &callback);
  /**
   * @brief 删除窗口鼠标右键弹起回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMiddleUpCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventMiddleDownHandel> EventMiddleDownCallbacks;
  /**
   * @brief 添加窗口鼠标中键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMiddleDownCallback(const HYWindowEventMiddleDownHandel &callback);
  /**
   * @brief 删除窗口鼠标中键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMiddleDownCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventLeftUpHandel> EventRightUpCallbacks;
  /**
   * @brief 添加窗口鼠标右键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventRightUpCallback(const HYWindowEventRightUpHandel &callback);
  /**
   * @brief 删除窗口鼠标右键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventRightUpCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventRightDownHandel> EventRightDownCallbacks;
  /**
   * @brief 添加窗口鼠标右键按下回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventRightDownCallback(const HYWindowEventRightDownHandel &callback);
  /**
   * @brief 删除窗口鼠标右键按下回调
   * @param id: 回调ID
   * */
  void UnRegisterEventRightDownCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventMouseMoveHandel> EventMouseMoveCallbacks;
  /**
   * @brief 添加窗口鼠标移动回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseMoveCallback(const HYWindowEventMouseMoveHandel &callback);
  /**
   * @brief 删除窗口鼠标移动回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseMoveCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventKeyDownHandel> EventKeyDownCallbacks;
  /**
   * @brief 添加窗口按下某键回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventKeyDownCallback(const HYWindowEventKeyDownHandel &callback);
  /**
   * @brief 删除窗口按下某键回调
   * @param id: 回调ID
   * */
  void UnRegisterEventKeyDownCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventKeyUpHandel> EventKeyUpCallbacks;
  /**
   * @brief 添加窗口放开某键回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventKeyUpCallback(const HYWindowEventKeyUpHandel &callback);
  /**
   * @brief 删除窗口放开某键回调
   * @param id: 回调ID
   * */
  void UnRegisterEventKeyUpCallback(uint32_t id);

  std::map<uint32_t, HYWindowEventMouseWheelHandel> EventMouseWheelCallbacks;
  /**
   * @brief 添加窗口滚轮被滚动回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseWheelCallback(const HYWindowEventMouseWheelHandel &callback);
  /**
   * @brief 删除窗口滚轮被滚动回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseWheelCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventCharInputHandel> EventCharInputCallbacks;
  /**
   * @brief 添加窗口字符输入回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventCharInputCallback(const HYWindowEventCharInputHandel &callback);
  /**
   * @brief 删除窗口字符输入回调
   * @param id: 回调ID
   * */
  void UnRegisterEventCharInputCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventMouseEnterHandel> EventMouseEnterCallbacks;
  /**
   * @brief 添加鼠标进入回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseEnterCallback(const HYWindowEventMouseEnterHandel &callback);
  /**
   * @brief 删除鼠标退出回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseEnterCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventMouseLeaveHandel> EventMouseLeaveCallbacks;
  /**
   * @brief 添加鼠标进入回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventMouseLeaveCallback(const HYWindowEventMouseLeaveHandel &callback);
  /**
   * @brief 删除鼠标退出回调
   * @param id: 回调ID
   * */
  void UnRegisterEventMouseLeaveCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventFocusGainedHandel> EventFocusGainedCallbacks;
  /**
   * @brief 添加获取焦点回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventFocusGainedCallback(const HYWindowEventFocusGainedHandel &callback);
  /**
   * @brief 删除获取焦点回调
   * @param id: 回调ID
   * */
  void UnRegisterEventFocusGainedCallback(uint32_t id);


  std::map<uint32_t, HYWindowEventFocusLostHandel> EventFocusLostCallbacks;
  /**
   * @brief 添加丢失焦点回调
   * @param callback: 回调函数
   * @return: 回调ID,用于取消回调
   * */
  uint32_t RegisterEventFocusLostCallback(const HYWindowEventFocusLostHandel &callback);
  /**
   * @brief 删除丢失焦点回调
   * @param id: 回调ID
   * */
  void UnRegisterEventFocusLostCallback(uint32_t id);


};


}// namespace HYGUI

#endif//HYGUI_EVENTWINDOW_H
