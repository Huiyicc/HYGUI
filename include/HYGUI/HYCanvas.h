//
// Created by 19254 on 24-9-30.
//

#ifndef HYGUI_HYCANVAS_H
#define HYGUI_HYCANVAS_H

#include <HYGUI/HYDefine.h>

class SkCanvas;

namespace HYGUI {

class HYCanvas: public HYClassBase {
public:
  ~HYCanvas() override;

  explicit HYCanvas();
  explicit HYCanvas(SkCanvas* ptr);
  HYCanvas(const HYCanvas& other);

private:
  SkCanvas* m_ptr;

public:
  [[nodiscard]] SkCanvas *get() const;
  SkCanvas *operator->() const;
  bool operator==(const nullptr_t &p) const;
  bool operator!() const;
  HYCanvas& operator=(const HYCanvas& other);
  HYCanvas& operator=(SkCanvas* other);
  explicit operator bool() const;

};

}

#endif//HYGUI_HYCANVAS_H
