//
// Created by 回忆 on 24-10-4.
//

#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <HYGUI/HYTypeDef.h>
#include <HYGUI/Keyboard.h>
#include <functional>
#include <iostream>

namespace HYGUI {

class HYWindow;
class HYRect;
class HYPoint;
class HYPointf;

template<typename T>
struct has_void_return;

template<typename Ret, typename... Args>
struct has_void_return<std::function<Ret(Args...)>> {
  static constexpr bool value = std::is_void_v<Ret>;
};

template<typename CALLTYPE, typename CALLTYPEPTR>
class HYEventRegistry {
public:
  void connect(const CALLTYPEPTR &callFunc) {
    callbacks.push_back(callFunc);
  }
  void connect(const CALLTYPE &callFunc) {
    callbacks.push_back(callFunc);
  }

  HYEventRegistry& operator+=(const CALLTYPE &callFunc) {
    connect(callFunc);
    return *this;
  }

  HYEventRegistry& operator+=(const CALLTYPEPTR &callFunc) {
    connect(callFunc);
    return *this;
  }

#ifdef _HYGUI_MODULE_
public:
#else
private:
#endif

  template<typename... Args>
  int operator()(Args &&...args) {
    for (auto &cb: callbacks) {
      if constexpr (has_void_return<decltype(priv)>::value) {
        // 无返回值
        cb(std::forward<Args>(args)...);
      } else {
        // 有返回值
        auto result = cb(std::forward<Args>(args)...);
        if (result != 0) {
          return result;
        }
      }
    }
    return 0;
  }

private:
  bool return_type_has_void() {
    // 萃取返回值类型
    return has_void_return<decltype(priv)>::value;
  }
  CALLTYPE priv;
  std::vector<CALLTYPE> callbacks;
};

enum HYWindowEvent : uint32_t {
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

typedef void (*HYWindowEventCreateHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_创建完毕
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventCreateHandel;

typedef void (*HYWindowEventBackgroundPaintHandelCall)(HYWindow *, void *, void *, HYRect *);
/**
 * @brief 窗口事件_背景重绘
 * @param HYWindow*: 窗口句柄
 * @param CanvasPtr: 背景画布指针
 * @param PaintPtr: 背景画笔指针
 * @param HYRect*: 背景区域
 * */
 typedef std::function<void(HYWindow *,HYCanvas* ,HYPaint*, HYRect*)> HYWindowEventBackgroundPaintHandel;

typedef void (*HYWindowEventRefreshHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_刷新
 * @param HYWindow*: 窗口句柄
 * @param PaintPtr: 背景画笔指针
 * @param HYRect*: 背景区域
 * */
typedef std::function<void(HYWindow *)> HYWindowEventRefreshHandel;

typedef bool (*HYWindowEventBeforeCloseHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_可否被关闭
 *
 * 返回true: 拦截, false: 放行
 *
 * @param HYWindow*: 窗口句柄
 * @result bool: 是否拦截
 * */
typedef std::function<bool(HYWindow *)> HYWindowEventBeforeCloseHandel;

typedef void (*HYWindowEventWillDestroyHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_即将销毁
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventWillDestroyHandel;

typedef void (*HYWindowEventMoveHandelCall)(HYWindow *, HYPoint *);
/**
 * @brief 窗口事件_位置改变
 * @param HYWindow*: 窗口句柄
 * @param HYPoint*: 新尺寸
 * */
typedef std::function<void(HYWindow *, HYPoint *)> HYWindowEventMoveHandel;

typedef void (*HYWindowEventResizeHandelCall)(HYWindow *, HYRect *);
/**
 * @brief 窗口事件_尺寸改变
 * @param HYWindow*: 窗口句柄
 * @param HYRect*: 新尺寸
 * */
typedef std::function<void(HYWindow *, HYRect *)> HYWindowEventResizeHandel;

typedef void (*HYWindowEventFirstActivateHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_首次激活
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventFirstActivateHandel;

typedef void (*HYWindowEventTrayHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_托盘事件
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventTrayHandel;

typedef void (*HYWindowEventShowHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_被显示
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventShowHandel;

typedef void (*HYWindowEventHideHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_被隐藏
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventHideHandel;

typedef void (*HYWindowEventLeftDownHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标左键按下
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventLeftDownHandel;

typedef void (*HYWindowEventLeftUpHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标左键放开
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventLeftUpHandel;

typedef void (*HYWindowEventRightUpHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标右键放开
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventRightUpHandel;

typedef void (*HYWindowEventRightDownHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标右键按下
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventRightDownHandel;

typedef void (*HYWindowEventMiddleUpHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标中键放开
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventMiddleUpHandel;

typedef void (*HYWindowEventMiddleDownHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标中键按下
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventMiddleDownHandel;

typedef void (*HYWindowEventMouseMoveHandelCall)(HYWindow *, int, int, HYKeymod);
/**
 * @brief 窗口事件_鼠标移动
 * @param HYWindow*: 窗口句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, int, int, HYKeymod)> HYWindowEventMouseMoveHandel;

typedef void (*HYWindowEventMouseEnterHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_鼠标进入
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventMouseEnterHandel;

typedef void (*HYWindowEventMouseLeaveHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_鼠标退出
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventMouseLeaveHandel;

typedef int (*HYWindowEventKeyDownHandelCall)(HYWindow *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod);
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

typedef int (*HYWindowEventKeyUpHandelCall)(HYWindow *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod);
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

typedef void (*HYWindowEventMouseWheelHandelCall)(HYWindow *, float, float, HYKeymod);
/**
 * @brief 窗口事件_滚轮被滚动
 * @param HYWindow*: 窗口句柄
 * @param float: x滚动距离
 * @param float: y滚动距离(一般只需要关注y)
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * */
typedef std::function<void(HYWindow *, float, float, HYKeymod)> HYWindowEventMouseWheelHandel;

typedef void (*HYWindowEventCharInputHandelCall)(HYWindow *, HYKeyCode, HYKeymod);
/**
 * @brief 窗口事件_字符输入
 * @param HYWindow*: 窗口句柄
 * @param HYKeyCode: 字符码
 * @param HYKeymod: 保留参数
 * */
typedef std::function<void(HYWindow *, HYKeyCode, HYKeymod)> HYWindowEventCharInputHandel;

typedef void (*HYWindowEventFocusGainedHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_获取焦点
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventFocusGainedHandel;

typedef void (*HYWindowEventFocusLostHandelCall)(HYWindow *);
/**
 * @brief 窗口事件_丢失焦点
 * @param HYWindow*: 窗口句柄
 * */
typedef std::function<void(HYWindow *)> HYWindowEventFocusLostHandel;


class HYWindowEventBase : public HYClassBase {
public:
  struct {
    /**
     * @brief  窗口事件_创建完毕
     */
    HYEventRegistry<HYWindowEventCreateHandel, HYWindowEventCreateHandelCall> OnCreate;

    /**
    * @brief  窗口事件_背景重绘
    */
    HYEventRegistry<HYWindowEventBackgroundPaintHandel, HYWindowEventBackgroundPaintHandelCall> OnBackgroundPaint;

    /**
    * @brief  窗口事件_刷新
    */
    HYEventRegistry<HYWindowEventRefreshHandel, HYWindowEventRefreshHandelCall> OnRefreshc;

    /**
    * @brief 窗口事件_可否被关闭
    */
    HYEventRegistry<HYWindowEventBeforeCloseHandel, HYWindowEventBeforeCloseHandelCall> OnBeforeClose;

    /**
    * @brief 窗口事件_即将销毁
    */
    HYEventRegistry<HYWindowEventWillDestroyHandel, HYWindowEventWillDestroyHandelCall> OnWillDestroy;

    /**
    * @brief 窗口事件_位置改变
    */
    HYEventRegistry<HYWindowEventMoveHandel, HYWindowEventMoveHandelCall> OnMove;

    /**
    * @brief 窗口事件_尺寸改变
    */
    HYEventRegistry<HYWindowEventResizeHandel, HYWindowEventResizeHandelCall> OnResize;

    /**
    * @brief 窗口事件_首次激活
    */
    HYEventRegistry<HYWindowEventFirstActivateHandel, HYWindowEventFirstActivateHandelCall> OnFirstActivate;

    /**
    * @brief 窗口事件_托盘事件
    */
    HYEventRegistry<HYWindowEventTrayHandel, HYWindowEventTrayHandelCall> OnTrayAction;

    /**
    * @brief 窗口事件_被显示
    */
    HYEventRegistry<HYWindowEventShowHandel, HYWindowEventShowHandelCall> OnShown;

    /**
    * @brief 窗口事件_被隐藏
    */
    HYEventRegistry<HYWindowEventHideHandel, HYWindowEventHideHandelCall> OnHidden;

    /**
    * @brief 窗口事件_鼠标左键按下
    */
    HYEventRegistry<HYWindowEventLeftDownHandel, HYWindowEventLeftDownHandelCall> OnLeftClickStart;

    /**
    * @brief 窗口事件_鼠标左键放开
    */
    HYEventRegistry<HYWindowEventLeftUpHandel, HYWindowEventLeftUpHandelCall> OnLeftClickEnd;

    /**
    * @brief 窗口事件_鼠标右键放开
    */
   HYEventRegistry<HYWindowEventRightUpHandel,HYWindowEventRightUpHandelCall> OnRightClickEnd;

   /**
    * @brief 窗口事件_鼠标右键按下
    */
   HYEventRegistry<HYWindowEventRightDownHandel,HYWindowEventRightDownHandelCall> OnRightClickStart;

   /**
    * @brief 窗口事件_鼠标中键放开
    */
   HYEventRegistry<HYWindowEventMiddleUpHandel,HYWindowEventMiddleUpHandelCall> OnMiddleClickEnd;

   /**
    * @brief 窗口事件_鼠标中键按下
    */
   HYEventRegistry<HYWindowEventMiddleDownHandel,HYWindowEventMiddleDownHandelCall> OnMiddleClickStart;

   /**
    * @brief 窗口事件_鼠标移动
    */
   HYEventRegistry<HYWindowEventMouseMoveHandel,HYWindowEventMouseMoveHandelCall> OnMouseMove;

   /**
    * @brief 窗口事件_鼠标进入
    */
   HYEventRegistry<HYWindowEventMouseEnterHandel,HYWindowEventMouseEnterHandelCall> OnMouseEnter;

   /**
    * @brief 窗口事件_鼠标退出
    */
   HYEventRegistry<HYWindowEventMouseLeaveHandel,HYWindowEventMouseLeaveHandelCall> OnMouseLeave;

   /**
    * @brief 窗口事件_按下某键
    */
   HYEventRegistry<HYWindowEventKeyDownHandel,HYWindowEventKeyDownHandelCall> OnKeyPress;

   /**
    * @brief 窗口事件_放开某键
    */
   HYEventRegistry<HYWindowEventKeyUpHandel,HYWindowEventKeyUpHandelCall> OnKeyRelease;

   /**
    * @brief 窗口事件_滚轮被滚动
    */
   HYEventRegistry<HYWindowEventMouseWheelHandel,HYWindowEventMouseWheelHandelCall> OnMouseScroll;

   /**
    * @brief 窗口事件_字符输入
    */
   HYEventRegistry<HYWindowEventCharInputHandel,HYWindowEventCharInputHandelCall> OnCharInput;

   /**
    * @brief 窗口事件_获取焦点
    */
   HYEventRegistry<HYWindowEventFocusGainedHandel,HYWindowEventFocusGainedHandelCall> OnFocusGained;

   /**
    * @brief 窗口事件_丢失焦点
    */
   HYEventRegistry<HYWindowEventFocusLostHandel,HYWindowEventFocusLostHandelCall> OnFocusLost;

  } Events;
};

}

#endif //EVENTBASE_H
