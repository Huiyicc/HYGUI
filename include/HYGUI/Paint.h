//
// Created by 19254 on 2024/6/17.
//

#ifndef HYGUI_PAINT_H
#define HYGUI_PAINT_H

#include <HYGUI/Define.h>
#include <HYGUI/Color.h>

namespace HYGUI {

void HYPaintSetColor(PaintPtr paint, HYARGB color);

void HYPaintSetARGB(PaintPtr paint, uint8_t a, uint8_t r, uint8_t g, uint8_t b);

}

#endif //HYGUI_PAINT_H
