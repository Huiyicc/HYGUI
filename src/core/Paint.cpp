//
// Created by 19254 on 2024/6/17.
//
#include "PrivateDefinition.h"
#include "HYGUI/Paint.h"
#include "include/core/SkShader.h"

namespace HYGUI {

void HYPaintSetColor(PaintPtr paint, HYARGB color) {
  paint->setColor(SkColorSetARGB(color.a, color.r, color.g, color.b));
}

void HYPaintSetARGB(PaintPtr paint, uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
  paint->setARGB(a, r, g, b);
}

void HYPaintDrawRect(CanvasPtr canvas,PaintPtr paint,const HYRect* rect) {
  canvas->drawRect(SkRect::MakeLTRB(rect->x, rect->y, rect->width, rect->height), *paint);
}

void HYPaintDrawRoundRect(CanvasPtr canvas,PaintPtr paint,const HYRect* rect,float rx,float ry) {
  canvas->drawRoundRect(SkRect::MakeLTRB(rect->x, rect->y, rect->width, rect->height), rx, ry, *paint);
}

void HYPaintSetShader(PaintPtr paint,ShaderPtr shader) {
  if (paint->getShader()) {
    HYResourceRemove(ResourceType::ResourceType_Shader, paint->getShader());
  }
  paint->setShader(sk_sp(shader));
  if (shader != nullptr) {
    HYResourceRemove(ResourceType::ResourceType_Shader, shader);
  }
}


}// namespace HYGUI