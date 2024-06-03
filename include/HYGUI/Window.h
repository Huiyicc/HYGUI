//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_WINDOW_H
#define HYGUI_WINDOW_H

#include "HYGUI/Define.h"
#include "HYGUI/String.h"

namespace HYGUI {

struct HYWindow {
  WINDOWHANDEL Handle = nullptr;
  VOIDPTRT OldProc = 0;
  VOIDPTR WindowCanvasTarget = nullptr; // HDC
  int Width = 0;
  int Height = 0;
  int X = 0;
  int Y = 0;

  SurfacePtr Surface = nullptr;
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
 * @param x 窗口左上角x坐标
 * @param y 窗口左上角y坐标
 * @param width 窗口宽度
 * @param height 窗口高度
 * @return
 */
HYWindow* HYWindowCreate(HYWindow* parent, const HYString &title, int x, int y, int width, int height);
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
uint32_t HYWindowMessageLoopDialog(HYWindow *wnd, HYWindow *parent= nullptr);

/**
 * @brief 窗口句柄获取窗口指针
 * @param handle 窗口句柄
 * @return
 */
HYWindow* HYWindowGetWindowFromHandle(WINDOWHANDEL handle);

/**
 * @brief 窗口钩子
 * @param wnd 窗口指针
 * @return
 */
void* HYWindowSkinHook(HYWindow *wnd);

}

#endif //HYGUI_WINDOW_H
