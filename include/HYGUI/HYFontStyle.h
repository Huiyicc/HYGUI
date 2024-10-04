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

  SkFontStyle* operator->() const;
  bool operator==(const nullptr_t&p) const;
  bool operator!() const;

private:
  std::shared_ptr<SkFontStyle> m_ptr;
};

};// namespace HYGUI


#endif//HYGUI_HYFONTSTYLE_H
