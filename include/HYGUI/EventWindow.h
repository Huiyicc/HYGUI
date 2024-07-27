//
// Created by 19254 on 24-7-28.
//

#ifndef HYGUI_EVENTWINDOW_H
#define HYGUI_EVENTWINDOW_H

#include "Keyboard.h"

namespace HYGUI {

class HYWindow;

enum HYWindowEvent {
  // ...
  // 预留事件
  // ...

  // 窗口创建完毕
  HYWindowEvent_Create = 100,
  // 窗口重绘
  HYWindowEvent_Paint,
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



}// namespace HYGUI

#endif//HYGUI_EVENTWINDOW_H
