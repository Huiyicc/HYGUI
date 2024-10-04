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

  SkCanvas* operator->() const;
  bool operator==(const nullptr_t&p) const;
  bool operator!() const;

private:
  std::shared_ptr<SkCanvas> m_ptr;
};

}

#endif//HYGUI_HYCANVAS_H
