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

  explicit HYSurface() = delete;
  explicit HYSurface(SkSurface* ptr);

  HYGUICLASS_HANDER_DEFINE(HYSurface, SkSurface);

};

};

#endif//HYGUI_HYSURFACE_H
