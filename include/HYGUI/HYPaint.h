//
// Created by 19254 on 24-10-3.
//

#ifndef HYGUI_HYPAINT_H
#define HYGUI_HYPAINT_H

#include <HYGUI/HYDefine.h>

class SkPaint;

namespace HYGUI {

class HYPaint: public HYClassBase {
public:
  ~HYPaint() override;

  explicit HYPaint();
  explicit HYPaint(SkPaint* ptr);

  HYGUICLASS_HANDER_DEFINE(HYPaint, SkPaint);

};

}



#endif//HYGUI_HYPAINT_H
