//
// Created by 19254 on 24-5-31.
//
#ifdef _HOST_WINDOWS_


#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include <dwmapi.h>

namespace HYGUI {

void window_hook_handel(HYWindow *windowPtr) {
  if (!windowPtr->Handle) return;
  //圆角窗口
//  HRGN hRgn;
//  RECT rect;
//  auto hwnd=(HWND) windowPtr->Handle;
//  GetWindowRect(hwnd, &rect);
//  hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, windowPtr->round, windowPtr->round);
//  SetWindowRgn(hwnd, hRgn, TRUE);
//  DeleteObject(hRgn);
}

void adjustwindow_by_sdl(HYWindowHandel window, void *newhandel) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  HWND hWnd = (HWND) newhandel;
  window->Handle = hWnd;
  SDL_GetWindowPosition(window->SDLWindow, &window->X, &window->Y);
  SDL_GetWindowSize(window->SDLWindow, &window->Width, &window->Height);
  window->ClientRect = {0, 0, window->Width, window->Height};
  window_hook_handel(window);
}

}// namespace HYGUI
#else
void _WINDW_WIN() {
  return;
}
#endif