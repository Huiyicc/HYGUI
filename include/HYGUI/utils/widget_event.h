//
// Created by 19254 on 24-10-20.
//

#ifndef HYGUI_WIDGET_EVENT_H
#define HYGUI_WIDGET_EVENT_H

#include <HYGUI/HYKeyCode.h>
#include <HYGUI/HYKeyboard.h>
#include <HYGUI/HYString.h>
#include <HYGUI/HYTypeDef.h>
#include <HYGUI/utils/event_base.h>

namespace HYGUI {
class HYWindow;
class HYWidget;
struct HYPoint;
struct HYRect;

/**
 * @brief 对象事件
 * */
enum class HYWidgetEvent : int32_t {
  // ...
  // 预留事件
  // ...

  // 组件消息
  HYWidgetEvent_Event  = 100,
  // 对象创建
  HYWidgetEvent_Create,
  // 对象销毁
  HYWidgetEvent_Destroy,
  // 对象重绘
  HYWidgetEvent_Paint,

  // 尺寸被改变
  HYWidgetEvent_Resize,
  // 位置被改变
  HYWidgetEvent_Move,
  // 被显示
  HYWidgetEvent_Show,
  // 被隐藏
  HYWidgetEvent_Hide,
  // 鼠标左键按下
  HYWidgetEvent_LeftDown,
  // 鼠标左键放开
  HYWidgetEvent_LeftUp,
  // 鼠标右键按下
  HYWidgetEvent_RightDown,
  // 鼠标右键按下
  HYWidgetEvent_RightUp,
  // 鼠标中键按下
  HYWidgetEvent_MiddleDown,
  // 鼠标中键放开
  HYWidgetEvent_MiddleUp,
  // 鼠标移动
  HYWidgetEvent_MouseMove,
  // 鼠标进入组件
  HYWidgetEvent_MouseEnter,
  // 鼠标离开组件
  HYWidgetEvent_MouseLeave,
  // 按下某键
  HYWidgetEvent_KeyDown,
  // 放开某键
  HYWidgetEvent_KeyUp,
  // 滚轮被滚动
  HYWidgetEvent_MouseWheel,
  // 字符输入
  HYWidgetEvent_CharInput,
  // 获取焦点
  HYWidgetEvent_FocusGained,
  // 失去焦点
  HYWidgetEvent_FocusLost,
};

struct HYWidgetEventInfo {
  HYWidgetEvent Event;
  HYWindow *Window;
  HYWidget *Object;
  uint64_t Param1;
  uint32_t Param2;
};

typedef int (*HYWidgetEventMessageHandelCall)(HYWindow *, HYWidget *, HYWidgetEvent, uint64_t, uint32_t);
/**
 * @brief 组件事件_消息事件
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param HYWidgetEvent: 事件类型,参考枚举值HYWidgetEvent
 * @param uint64_t: 参数1
 * @param uint32_t: 参数2
 * */
typedef std::function<int(HYWindow *, HYWidget *, HYWidgetEvent, uint64_t, uint32_t)> HYWidgetEventMessageHandel;

typedef void(*HYWidgetEventCreateHandelCall)(HYWindow *, HYWidget *);
/**
 * @brief 组件事件_创建
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYWidget *)> HYWidgetEventCreateHandel;

typedef void (*HYWidgetEventDestroyHandelCall)(HYWindow *, HYWidget *);
  /**
 * @brief 组件事件_销毁
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYWidget *)> HYWidgetEventDestroyHandel;

typedef int (*HYWidgetEventPaintHandelCall)(HYWindow *, HYWidget *);
/**
 * @brief 组件事件_绘制
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *)> HYWidgetEventPaintHandel;

/**
 * @brief 组件事件_位置改变
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param HYPoint*: 新位置
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, HYPoint *)> HYWidgetEventMoveHandel;

/**
 * @brief 组件事件_尺寸改变
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param HYRect*: 新尺寸
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, HYRect *)> HYWidgetEventResizeHandel;

/**
 * @brief 组件事件_显示
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYWidget *)> HYWidgetEventShowHandel;

/**
 * @brief 组件事件_隐藏
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYWidget *)> HYWidgetEventHideHandel;

/**
 * @brief 组件事件_鼠标左键按下
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventLeftDownHandel;

/**
 * @brief 组件事件_鼠标左键放开
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventLeftUpHandel;

/**
 * @brief 组件事件_鼠标右键放开
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventRightUpHandel;

/**
 * @brief 组件事件_鼠标右键按下
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventRightDownHandel;

/**
 * @brief 组件事件_鼠标中键放开
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventMiddleUpHandel;

/**
 * @brief 组件事件_鼠标中键按下
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventMiddleDownHandel;

/**
 * @brief 组件事件_鼠标移动
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, int, int, HYKeymod)> HYWidgetEventMouseMoveHandel;

/**
 * @brief 组件事件_鼠标进入
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *)> HYWidgetEventMouseEnterHandel;

/**
 * @brief 组件事件_鼠标退出
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *)> HYWidgetEventMouseLeaveHandel;

/**
 * @brief 组件事件_按下某键
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param HYKeyboardID: 键盘ID
 * @param HYScancode: 键盘扫描键值 HY_SCANCODE_
 * @param HYKeyCode: 键盘键值 HY_KEY_
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod)> HYWidgetEventKeyDownHandel;

/**
 * @brief 组件事件_放开某键
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param HYKeyboardID: 键盘ID
 * @param HYScancode: 键盘扫描键值 HY_SCANCODE_
 * @param HYKeyCode: 键盘键值 HY_KEY_
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, HYKeyboardID, HYScancode, HYKeyCode, HYKeymod)> HYWidgetEventKeyUpHandel;

/**
 * @brief 组件事件_滚轮被滚动
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param float: x滚动距离
 * @param float: y滚动距离(一般只需要关注y)
 * @param HYKeymod: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, float, float, HYKeymod)> HYWidgetEventMouseWheelHandel;

/**
 * @brief 组件事件_字符输入
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * @param HYKeyCode: 字符码
 * @param HYKeymod: 保留参数
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYWidget *, HYKeyCode, HYKeymod)> HYWidgetEventCharInputHandel;

/**
 * @brief 组件事件_获取焦点
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYWidget *)> HYWidgetEventFocusGainedHandel;

/**
 * @brief 组件事件_丢失焦点
 * @param HYWindow*: 窗口句柄
 * @param HYWidget*: 组件句柄
 * */
typedef std::function<void(HYWindow *, HYWidget *)> HYWidgetEventFocusLostHandel;

class HYWidgetEventBase : public HYClassBase {
public:
  struct {
    /**
     * @brief 组件事件_处理消息
     *
     * @param HYWindow* window_handle: 窗口句柄，指向当前窗口的实例。
     * @param HYWidget* widget_handle: 组件句柄，指向当前组件的实例。
     * @param HYWidgetEvent event_type: 事件类型，参考枚举值 HYWidgetEvent。
     * @param uint64_t param1: 事件处理的第一个参数，具体含义依赖于事件类型。
     * @param uint32_t param2: 事件处理的第二个参数，具体含义依赖于事件类型。
     * @return 返回值：0放行，1拦截
     */
    HYEventRegistry<HYWidgetEventMessageHandel, HYWidgetEventMessageHandelCall> OnEvent;

    /**
     * @brief 组件事件_创建
     *
     * @param HYWindow* window_handle: 窗口句柄，指向当前窗口的实例。
     * @param HYWidget* widget_handle: 组件句柄，指向当前组件的实例。
     */
    HYEventRegistry<HYWidgetEventCreateHandel, HYWidgetEventCreateHandelCall> OnCreate;


    HYEventRegistry<HYWidgetEventDestroyHandel, HYWidgetEventDestroyHandelCall> OnDestroy;

    HYEventRegistry<HYWidgetEventPaintHandel, HYWidgetEventPaintHandelCall> OnPaint;



  } Events;


};

}// namespace HYGUI

#endif//HYGUI_WIDGET_EVENT_H
