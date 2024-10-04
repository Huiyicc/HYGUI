//
// Created by 回忆 on 24-10-4.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "./EventBase.h"
#include <HYGUI/HYContext.h>
#include <HYGUI/HYRect.h>
#include <HYGUI/HYTypeDef.h>
#include <HYGUI/HYString.h>

namespace HYGUI {

#ifdef _HOST_WINDOWS_
constexpr int WINDOWCREATEPOINT_USEDEFAULT = CW_USEDEFAULT;
#elif defined(_HOST_APPLE_) || defined(_HOST_LINUX_)
#include <limits>
constexpr int WINDOWCREATEPOINT_USEDEFAULT = std::numeric_limits<int>::max();
#endif


struct WindowHandelInfo {
#ifdef _HOST_LINUX_
  bool isWayland = false;
  /**
  * 显示字段
  * 当isWayland为true时为struct wl_display *display
  * 当isWayland为false时为Display * xdisplay (x11)
  */
  VOIDPTR handle = nullptr;
  /**
   * 保留字段
   * 当isWayland为true时为struct wl_surface * surface
   * 当isWayland为false时为Window xwindow (x11)
   */
  uintptr_t reserve = 0;
#elif defined(_HOST_WINDOWS_)
  /**
  * 窗口句柄
  */
  HWND handle = nullptr;
#elif defined(_HOST_APPLE_)
  // NSWindow*
  VOIDPTR handle = nullptr;
#endif
};


class HYWindow : public HYEventBase {
public:

  WindowHandelInfo GetHandel() const;
  ~HYWindow();
private:
  HYWindow();

  friend class HYWindowBuilder;

private:
  int m_ID = 0;
  int m_x = WINDOWCREATEPOINT_USEDEFAULT;
  int m_y = WINDOWCREATEPOINT_USEDEFAULT;
  int m_width = 800;
  int m_height = 600;

  HYRect m_ClientRect = {0};

  HYString m_title;
  HYGrDirectContext m_GrCtx;
  SDL_GLContext m_SDLOpenGl = nullptr;
  SDL_Window* m_SDLWindow = nullptr;
};

}// namespace HYGUI

#endif//WINDOW_H
