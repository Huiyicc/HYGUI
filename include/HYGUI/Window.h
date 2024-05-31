//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_WINDOW_H
#define HYGUI_WINDOW_H

#include "HYGUI/Define.h"
#include "HYGUI/String.h"

namespace HYGUI {

struct HYWindow {
  VOIDPTR Handle = nullptr;

};

/**
 * @brief 注册窗口类
 * @param className 窗口类名
 * @param iconPath 图标路径
 * @param cursorPath 光标路径
 * @return
 */
bool HYWindowRegisterClass(const HYString &className, const HYString &iconPath = "", const HYString &cursorPath = "");

HYWindow* HYWindowCreate(HYWindow* parent, const HYString &title, int x, int y, int width, int height);
bool HYWindowShow(HYWindow *wnd);
uint32_t HYWindowMessageLoop(HYWindow *wnd);
uint32_t HYWindowMessageLoopDialog(HYWindow *wnd, HYWindow *parent);

}

#endif //HYGUI_WINDOW_H
