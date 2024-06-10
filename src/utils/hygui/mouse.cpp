//
// Created by 19254 on 24-6-9.
//
#include "HYGUI/Mouse.h"
#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif

namespace HYGUI {
#ifdef _HOST_WINDOWS_
HYPoint HYMouseGetPosition() {

  POINT point;
  GetCursorPos(&point);
  return {point.x, point.y};
}
#elif defined(_HOST_MACOS_)
#error "Unsupported platform"
#endif

}
