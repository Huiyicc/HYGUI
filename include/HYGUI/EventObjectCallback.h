//
// Created by 19254 on 24-7-15.
//

#ifndef HYGUI_EVENTOBJECTCALLBACK_H
#define HYGUI_EVENTOBJECTCALLBACK_H

#include "Keyboard.h"

namespace HYGUI {

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


}// namespace HYGUI


#endif//HYGUI_EVENTOBJECTCALLBACK_H
