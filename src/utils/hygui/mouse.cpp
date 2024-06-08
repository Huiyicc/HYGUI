//
// Created by 19254 on 24-6-9.
//
#include "HYGUI/Mouse.h"
#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif

namespace HYGUI {

HYPoint HYMouseGetPosition() {
  #ifdef _HOST_WINDOWS_
  POINT point;
  GetCursorPos(&point);
  return {point.x, point.y};
  #else
  #error "Unsupported platform"
  #endif
}

}
