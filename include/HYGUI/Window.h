//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_WINDOW_H
#define HYGUI_WINDOW_H

#include "HYGUI/Define.h"
#include "HYGUI/String.h"
#include "HYGUI/Color.h"
#include "HYGUI/Event.h"
#include "HYGUI/Object.h"

#ifdef _HOST_WINDOWS_

#include <windows.h>

#endif

namespace HYGUI {

#ifdef _HOST_WINDOWS_
constexpr int WINDOWCREATEPOINT_USEDEFAULT CW_USEDEFAULT;
#else
#error "Unsupported platform"
#endif

struct HYWindow {
  WINDOWHANDEL Handle = nullptr;
  VOIDPTRT OldProc = 0;
  SurfacePtr Surface = nullptr;
  CanvasPtr Canvas = nullptr;
  VOIDPTR WindowCanvasTarget = nullptr; // HDC
  VOIDPTR WindowLayeredCanvas = nullptr;
  VOIDPTR CustomBmp = nullptr;
  int Width = 0; // 窗口宽度
  int Height = 0; // 窗口高度
  int X = 0; // 窗口左上角x坐标
  int Y = 0; // 窗口左上角y坐标
  HYRect ClientRect = {0, 0, 0, 0}; // 客户区域

  int BackGroundColor = 0; // 背景颜色
  int Diaphaneity = 255; // 透明度
  HYObjectEventQueue EventQueue;


  std::set<HYObject *> Children;
};

/**
 * @brief 注册窗口类
 * @param className 窗口类名
 * @param iconPath 图标路径
 * @param cursorPath 光标路径
 * @return
 */
bool HYWindowRegisterClass(const HYString &className, const HYString &iconPath = "", const HYString &cursorPath = "");

/**
 * @brief 创建窗口
 * @param parent 父窗口
 * @param title 窗口标题
 * @param x 窗口左上角x坐标 WINDOWCREATEPOINT_
 * @param y 窗口左上角y坐标 WINDOWCREATEPOINT_
 * @param width 窗口宽度
 * @param height 窗口高度
 * @return
 */
HYWindow *HYWindowCreate(HYWindow *parent, const HYString &title,
                         int x = WINDOWCREATEPOINT_USEDEFAULT,
                         int y = WINDOWCREATEPOINT_USEDEFAULT,
                         int width = 800,
                         int height = 600);

/**
 * @brief 销毁窗口
 * @param wnd 窗口指针
 */
void HYWindowDestroy(HYWindow *wnd);

/**
 * @brief 显示窗口
 * @param wnd 窗口指针
 * @return
 */
bool HYWindowShow(HYWindow *wnd);

/**
 * @brief 窗口消息循环
 * @param wnd 窗口指针
 * @return
 */
uint32_t HYWindowMessageLoop(HYWindow *wnd);

/**
 * @brief 对话框窗口消息循环
 * @param wnd 窗口指针
 * @param parent 父窗口指针
 * @return
 */
uint32_t HYWindowMessageLoopDialog(HYWindow *wnd, HYWindow *parent = nullptr);

/**
 * @brief 窗口句柄获取窗口指针
 * @param handle 窗口句柄
 * @return
 */
HYWindow *HYWindowGetWindowFromHandle(WINDOWHANDEL handle);

/**
 * @brief 挂接窗口皮肤
 * @param wnd 窗口指针
 * @param backGroundColor 背景颜色 RGB
 * @param diaphaneity 窗口透明度
 */
void HYWindowSkinHook(HYWindow *wnd,HYRGB backGroundColor,int diaphaneity);

/**
 * @brief 发送窗口事件
 * @param window 窗口指针
 * @param event 事件
 * @param param1 参数1
 * @param param2 参数2
 */
void HYWindowSendEvent(HYWindow *window, uint32_t event, intptr_t param1, intptr_t param2);

}

#endif //HYGUI_WINDOW_H
