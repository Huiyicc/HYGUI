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

struct HYPointf {
  float x = 0;
  float y = 0;

  explicit operator HYPoint() const {
    return {static_cast<int>(x), static_cast<int>(y)};
  }

  HYPointf operator+(const HYPointf &point) const {
    return {x + point.x, y + point.y};
  }
  bool operator==(const HYPointf &point) const {
    return x == point.x && y == point.y;
  }
};

/**
 * 生成基于二维坐标(x, y)的长整型参数(lParam)。
 *
 * @param x 横坐标，类型为无符号短整型。
 * @param y 纵坐标，类型为无符号短整型。
 * @return 返回一个无符号长整型值，代表结合了x和y坐标的lParam。
 */
uint32_t HYPointGenLParam(uint16_t x, uint16_t y);

/**
 * 从长整型参数(lParam)中解析出二维坐标点。
 *
 * @param lParam 长整型参数，包含x和y坐标信息。
 * @return 返回一个HYPoint结构体，包含解析出的x和y坐标。
 */
HYPoint HYPointFromLParam(uint32_t lParam);

/**
 * 判断一个点是否位于矩形内部。
 *
 * @param point 待检测的点，由HYPoint结构体表示。
 * @param rectangle 检测用的矩形，由HYRect结构体表示。
 * @return 如果点位于矩形内部，返回true；否则返回false。
 */
bool HYPointIsInsideRectangle(const HYPoint& point, const HYRect& rectangle);

}

#endif //HYGUI_POINT_H
