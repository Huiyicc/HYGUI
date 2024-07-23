//
// Created by 19254 on 24-7-15.
//

#ifndef HYGUI_EVENTOBJECTCALLBACK_H
#define HYGUI_EVENTOBJECTCALLBACK_H


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
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventLeftDownHandel;

/**
 * @brief 组件事件_鼠标左键放开
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventLeftUpHandel;

/**
 * @brief 组件事件_鼠标右键放开
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventRightUpHandel;

/**
 * @brief 组件事件_鼠标右键按下
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventRightDownHandel;

/**
 * @brief 组件事件_鼠标移动
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventMouseMoveHandel;

/**
 * @brief 组件事件_被双击
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 鼠标x坐标
 * @param int: 鼠标y坐标
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventDoubleClickHandel;

/**
 * @brief 组件事件_按下某键
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 键盘键值
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int)> HYObjectEventKeyDownHandel;

/**
 * @brief 组件事件_放开某键
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 键盘键值
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int)> HYObjectEventKeyUpHandel;

/**
 * @brief 组件事件_滚轮被滚动
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 滚动距离
 * @param int: 功能键状态,参见常量定义 HY_KMOD_
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int)> HYObjectEventMouseWheelHandel;

/**
 * @brief 组件事件_字符输入
 * @param HYWindow*: 窗口句柄
 * @param HYObject*: 组件句柄
 * @param int: 字符码
 * @param int: 保留参数
 * @result 0: 放行, 1: 拦截
 * */
typedef std::function<int(HYWindow *, HYObject *, int, int)> HYObjectEventCharInputHandel;


}// namespace HYGUI


#endif//HYGUI_EVENTOBJECTCALLBACK_H
