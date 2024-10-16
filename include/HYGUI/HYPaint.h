//
// Created by 19254 on 24-10-3.
//

#ifndef HYGUI_HYPAINT_H
#define HYGUI_HYPAINT_H

#include <HYGUI/HYColor.h>
#include <HYGUI/HYDefine.h>
#include <HYGUI/HYRect.h>

class SkPaint;

namespace HYGUI {

class HYPaint : public HYClassBase {
public:
  ~HYPaint() override;

  explicit HYPaint();
  explicit HYPaint(SkPaint *ptr);

  HYGUICLASS_HANDER_DEFINE(HYPaint, SkPaint);

  void SetAntiAlias(bool aa);

public:
  void SetColor(const HYARGB &color);
  void SetColor(const HYRGB &color);

  void SetARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
  void SetARGB(const HYARGB &color);
};

}// namespace HYGUI


#endif//HYGUI_HYPAINT_H
