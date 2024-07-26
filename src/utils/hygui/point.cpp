//
// Created by 19254 on 24-6-11.
//
#include "HYGUI/Point.h"
#include <cstdint>
#include <cstring>

namespace HYGUI {

uint32_t HYPointGenWParam(uint16_t x, uint16_t y) {
  return ((uint32_t)x & 0xFFFF) | (((uint32_t)y) << 16);
}

HYPoint HYPointFromWParam(uint32_t wParam) {
  return {
    (int32_t)(int(wParam) & 0xFFFF),
    (int32_t)((int(wParam) >> 16) & 0xFFFF)
  };
}

bool HYPointIsInsideRectangle(const HYPoint& point, const HYRect& rectangle) {
  if (point.x >= rectangle.x && point.x <= (rectangle.x + rectangle.width)) {
    if (point.y >= rectangle.y && point.y <= (rectangle.y + rectangle.height)) {
      return true;
    }
  }
  return false;
}

HYPointf HYPointfFromWParam(int64_t combined) {
  auto ia = static_cast<int32_t>(combined >> 32);
  auto ib = static_cast<int32_t>(combined & 0xFFFFFFFF);
  float a, b;
  std::memcpy(&a, &ia, sizeof(a));
  std::memcpy(&b, &ib, sizeof(b));
  return {a, b};
}

int64_t HYPointfGenWParam(float x, float y) {
  int32_t ia, ib;
  std::memcpy(&ia, &x, sizeof(ia));
  std::memcpy(&ib, &y, sizeof(ib));

  return static_cast<int64_t>(ia) << 32 | (static_cast<uint32_t>(ib) & 0xFFFFFFFF);
}

}
