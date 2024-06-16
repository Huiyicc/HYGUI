//
// Created by 19254 on 24-6-9.
//
#include "HYGUI/Mouse.h"
#include "SDL2/SDL.h"
#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif

namespace HYGUI {

HYPoint HYMouseGetPosition() {
  HYPoint point;
  SDL_GetGlobalMouseState(&point.x,&point.y);
  return point;
}

}
