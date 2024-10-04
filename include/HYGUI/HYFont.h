//
// Created by 19254 on 24-10-3.
//

#ifndef HYGUI_HYFONT_H
#define HYGUI_HYFONT_H

#include <HYGUI/HYDefine.h>

class SkFont;

namespace HYGUI {

class HYFont: public HYClassBase {
public:
  ~HYFont() override;

  explicit HYFont();
  explicit HYFont(SkFont* ptr);

  HYGUICLASS_HANDER_DEFINE(HYFont, SkFont);

};

}

#endif//HYGUI_HYFONT_H
