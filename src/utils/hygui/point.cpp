//
// Created by 19254 on 24-6-11.
//
#include "HYGUI/Point.h"

namespace HYGUI {

uint32_t HYPointGenLParam(uint16_t x, uint16_t y) {
  return ((uint32_t)x & 0xFFFF) | (((uint32_t)y) << 16);
}

HYPoint HYPointFromLParam(uint32_t lParam) {
  return {
    (int16_t)(lParam & 0xFFFF),
    (int16_t)((lParam >> 16) & 0xFFFF)
  };
}


}
