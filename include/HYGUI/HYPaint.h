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

  SkPaint* operator->();
  bool operator!();

private:
  std::shared_ptr<SkPaint> m_ptr;
};

}



#endif//HYGUI_HYPAINT_H
