//
// Created by 19254 on 24-10-3.
//

#ifndef HYGUI_HYFONTSTYLE_H
#define HYGUI_HYFONTSTYLE_H

#include <HYGUI/HYDefine.h>

class SkFontStyle;

namespace HYGUI {

class HYFontStyle : public HYClassBase {
public:
  ~HYFontStyle() override;

  explicit HYFontStyle();
  explicit HYFontStyle(SkFontStyle* ptr);

  HYGUICLASS_HANDER_DEFINE(HYFontStyle, SkFontStyle);

};

};// namespace HYGUI


#endif//HYGUI_HYFONTSTYLE_H
