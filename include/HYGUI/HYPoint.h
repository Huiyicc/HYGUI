//
// Created by 回忆 on 24-10-4.
//

#ifndef HYPOINT_H
#define HYPOINT_H

#include <cstdint>

namespace HYGUI {
struct HYRect;

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
  float x = 0.0f;
  float y = 0.0f;

  HYPointf() = default;
  HYPointf(float X, float Y) {
    x = X;
    y = Y;
  };

  explicit HYPointf(const HYPoint &point) {
    x = point.x;
    y = point.y;
  }

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
 * 生成基于二维坐标(x, y)的长整型参数(wParam)。
 *
 * @param x 横坐标，类型为无符号短整型。
 * @param y 纵坐标，类型为无符号短整型。
 * @return 返回一个无符号长整型值，代表结合了x和y坐标的wParam。
 */
uint32_t HYPointGenWParam(uint16_t x, uint16_t y);

/**
 * 从长整型参数(wParam)中解析出二维坐标点。
 *
 * @param lParam 长整型参数，包含x和y坐标信息。
 * @return 返回一个HYPoint结构体，包含解析出的x和y坐标。
 */
HYPoint HYPointFromWParam(uint32_t lParam);

/**
 * 判断一个点是否位于矩形内部。
 *
 * @param point 待检测的点，由HYPoint结构体表示。
 * @param rectangle 检测用的矩形，由HYRect结构体表示。
 * @return 如果点位于矩形内部，返回true；否则返回false。
 */
bool HYPointIsInsideRectangle(const HYPoint &point, const HYRect &rectangle);

/**
 * 从长整型参数(wParam)中解析出二维坐标点(float)。
 *
 * @param wParam 长整型参数，包含x和y坐标信息。
 * @return 返回一个HYPointf结构体，包含解析出的x和y坐标。
 * */
HYPointf HYPointfFromWParam(int64_t wParam);

/**
 * 生成基于二维坐标(x, y)的长整型参数(wParam)。
 *
 * @param x 横坐标。
 * @param y 纵坐标。
 * @return 返回一个长整型值，代表结合了x和y坐标的wParam。
 */
int64_t HYPointfGenWParam(float x, float y);

}// namespace HYGUI

#endif//HYPOINT_H
