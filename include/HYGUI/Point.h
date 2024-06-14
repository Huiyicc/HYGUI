//
// Created by 19254 on 24-6-11.
//

#ifndef HYGUI_POINT_H
#define HYGUI_POINT_H

#include <cstdint>

namespace HYGUI {

struct HYRect {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

struct HYPoint {
  int x = 0;
  int y = 0;

  HYPoint operator+(const HYPoint &point) const {
    return {x + point.x, y + point.y};
  }
  bool operator==(const HYPoint &point) const {
    return x == point.x && y == point.y;
  }
};

uint32_t HYPointGenLParam(uint16_t x, uint16_t y);
HYPoint HYPointFromLParam(uint32_t lParam);

}

#endif //HYGUI_POINT_H
