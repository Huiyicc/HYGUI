//
// Created by 19254 on 24-6-9.
//
#include "HYGUI/Mouse.h"
#include "HYGUI/Window.h"
#include "SDL3/SDL.h"
#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif

namespace HYGUI {

HYPointf HYMouseGetPosition() {
  HYPointf point;
  SDL_GetGlobalMouseState(&point.x, &point.y);
  return point;
}

HYPointf HYMouseGetPositionFromWindow(HYWindow *window) {
  HYPointf point;
  SDL_GetGlobalMouseState(&point.x, &point.y);
  if (window) {
    point.x -= static_cast<float>(window->X);
    point.y -= static_cast<float>(window->Y);
  }
  return point;
}

}// namespace HYGUI
