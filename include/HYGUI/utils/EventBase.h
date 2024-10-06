//
// Created by 回忆 on 24-10-4.
//

#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <HYGUI/HYTypeDef.h>
#include <HYGUI/Keyboard.h>
#include <functional>
#include <set>

namespace HYGUI {

class HYWindow;
class HYRect;
class HYPoint;
class HYPointf;

// // 函数指针版本
// template<typename Ret, typename... Args>
// class HYEventRegistry<Ret (*)(Args...)> {
// public:
//   void connect(Ret (*callFunc)(Args...)) {
//     callbacks.insert(callFunc);
//   }
//
//   void operator()(Args... args) {
//     for (auto &cb: callbacks) {
//       cb(args...);
//     }
//   }
//
// private:
//   std::set<Ret (*)(Args...)> callbacks;
// };
//
// // std::function 版本
// template<typename Ret, typename... Args>
// class HYEventRegistry<std::function<Ret(Args...)>> {
// public:
//   void connect(const std::function<Ret(Args...)> &callFunc) {
//     callbacks.insert(callFunc);
//   }
//
//   void operator()(Args... args) {
//     for (auto &cb: callbacks) {
//       cb(args...);
//     }
//   }
//
// private:
//   std::set<std::function<Ret(Args...)>> callbacks;
// };

template<typename FUNCALL>
class HYEventRegistry {
public:
  void connect(const FUNCALL &callFunc) {
    callbacks.insert(callFunc);
  }

 template<typename... Args>
 void operator()(Args&&... args) {
   for (auto &cb: callbacks) {
     cb(std::forward<Args>(args)...);
   }
 }

private:
  std::vector<FUNCALL> callbacks;
};


enum HYWindowEvent:uint32_t {
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
typedef std::function<void(HYWindow *, void *, void *, HYRect *)> HYWindowEventBackgroundPaintHandel;
// typedef std::function<void(HYWindow *,CanvasPtr ,PaintPtr, HYRect*)> HYWindowEventBackgroundPaintHandel;

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


class HYWindowEventBase : public HYClassBase {
public:
  struct{
    /**
     * @brief  窗口事件_创建完毕
     */
    HYEventRegistry<HYWindowEventCreateHandel> Create;

    /**
    * @brief  窗口事件_背景重绘
    */
    HYEventRegistry<HYWindowEventBackgroundPaintHandel> BackgroundPaint;

   /**
    * @brief  窗口事件_刷新
    */
   HYEventRegistry<HYWindowEventRefreshHandel> Refresh;

   /**
    * @brief 窗口事件_可否被关闭
    */
   HYEventRegistry<HYWindowEventBeforeCloseHandel> BeforeClose;

   /**
    * @brief 窗口事件_即将销毁
    */
   HYEventRegistry<HYWindowEventWillDestroyHandel> WillDestroy;

   /**
    * @brief 窗口事件_位置改变
    */
   HYEventRegistry<HYWindowEventMoveHandel> Move;

   /**
    * @brief 窗口事件_尺寸改变
    */
   HYEventRegistry<HYWindowEventResizeHandel> Resize;

   /**
    * @brief 窗口事件_首次激活
    */
   HYEventRegistry<HYWindowEventFirstActivateHandel> FirstActivate;

   /**
    * @brief 窗口事件_托盘事件
    */
   HYEventRegistry<HYWindowEventTrayHandel> Tray;

   /**
    * @brief 窗口事件_被显示
    */
   HYEventRegistry<HYWindowEventShowHandel> Shown;

   /**
    * @brief 窗口事件_被隐藏
    */
   HYEventRegistry<HYWindowEventShowHandel> Hidden;

   /**
    * @brief 窗口事件_鼠标左键按下
    */
   HYEventRegistry<HYWindowEventLeftDownHandel> LeftDown;

   /**
    * @brief 窗口事件_鼠标左键放开
    */
   HYEventRegistry<HYWindowEventLeftUpHandel> LeftUp;

   /**
    * @brief 窗口事件_鼠标右键放开
    */
   HYEventRegistry<HYWindowEventRightUpHandel> RightUp;

   /**
    * @brief 窗口事件_鼠标右键按下
    */
   HYEventRegistry<HYWindowEventRightDownHandel> RightDown;

   /**
    * @brief 窗口事件_鼠标中键放开
    */
   HYEventRegistry<HYWindowEventMiddleUpHandel> MiddleUp;

   /**
    * @brief 窗口事件_鼠标中键按下
    */
   HYEventRegistry<HYWindowEventMiddleDownHandel> MiddleDown;

   /**
    * @brief 窗口事件_鼠标移动
    */
   HYEventRegistry<HYWindowEventMouseMoveHandel> MouseMove;

   /**
    * @brief 窗口事件_鼠标进入
    */
   HYEventRegistry<HYWindowEventMouseEnterHandel> MouseEnter;

   /**
    * @brief 窗口事件_鼠标退出
    */
   HYEventRegistry<HYWindowEventMouseLeaveHandel> MouseLeave;

   /**
    * @brief 窗口事件_按下某键
    */
   HYEventRegistry<HYWindowEventKeyDownHandel> KeyDown;

   /**
    * @brief 窗口事件_放开某键
    */
   HYEventRegistry<HYWindowEventKeyUpHandel> KeyUp;

   /**
    * @brief 窗口事件_滚轮被滚动
    */
   HYEventRegistry<HYWindowEventMouseWheelHandel> MouseWheel;

   /**
    * @brief 窗口事件_字符输入
    */
   HYEventRegistry<HYWindowEventCharInputHandel> CharInput;

   /**
    * @brief 窗口事件_获取焦点
    */
   HYEventRegistry<HYWindowEventFocusGainedHandel> FocusGained;

   /**
    * @brief 窗口事件_丢失焦点
    */
   HYEventRegistry<HYWindowEventFocusLostHandel> FocusLost;

  } Events;
};

}

#endif //EVENTBASE_H
