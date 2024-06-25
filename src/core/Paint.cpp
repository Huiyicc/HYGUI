//
// Created by 19254 on 2024/6/17.
//
#include "HYGUI/Paint.h"

namespace HYGUI {

void HYPaintSetColor(PaintPtr paint, HYARGB color) {
  // 无硬件加速情况下颜色空间使用的是BGRA,所以这里要注意一下
  // paint->setColor(SkColorSetARGB(color.a, color.b, color.g, color.r));
  paint->setColor(SkColorSetARGB(color.a, color.r, color.g, color.b));
}

void HYPaintSetARGB(PaintPtr paint, uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
  paint->setARGB(a, r, g, b);
}


}// namespace HYGUI