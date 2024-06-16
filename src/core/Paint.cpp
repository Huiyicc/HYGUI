//
// Created by 19254 on 2024/6/17.
//
#include "HYGUI/Paint.h"

namespace HYGUI {

void HYPaintSetColor(PaintPtr paint, HYARGB color) {
  // 大多数情况下颜色空间使用的是BGRA,所以这里要注意一下
  paint->setColor(SkColorSetARGB(color.a, color.b, color.g, color.r));
}

}