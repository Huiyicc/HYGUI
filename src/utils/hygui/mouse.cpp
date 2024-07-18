//
// Created by 19254 on 24-6-9.
//
#include "HYGUI/Mouse.h"
#include "SDL3/SDL.h"
#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif

namespace HYGUI {

HYPointf HYMouseGetPosition() {
  HYPointf point;
  SDL_GetGlobalMouseState(&point.x,&point.y);
  return point;
}

}
