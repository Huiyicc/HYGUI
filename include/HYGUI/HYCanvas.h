//
// Created by 19254 on 24-9-30.
//

#ifndef HYGUI_HYCANVAS_H
#define HYGUI_HYCANVAS_H

#include <HYGUI/HYDefine.h>

class SkCanvas;

namespace HYGUI {

class HYCanvas: private HYClassBase {
public:
  ~HYCanvas() override;

  explicit HYCanvas();
  explicit HYCanvas(SkCanvas* ptr);

  HYGUICLASS_HANDER_DEFINE(HYCanvas, SkCanvas);

};

}

#endif//HYGUI_HYCANVAS_H
