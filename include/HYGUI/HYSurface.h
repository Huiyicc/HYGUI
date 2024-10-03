//
// Created by 19254 on 24-9-25.
//

#ifndef HYGUI_HYSURFACE_H
#define HYGUI_HYSURFACE_H

#include <HYGUI/HYDefine.h>

class SkSurface;

namespace HYGUI {

class HYSurface : public HYClassBase {
public:
  ~HYSurface() override;

  explicit HYSurface();
  explicit HYSurface(SkSurface* ptr);

  SkSurface* operator->();
  bool operator!();

private:
  std::shared_ptr<SkSurface> m_ptr;
};

};

#endif//HYGUI_HYSURFACE_H
