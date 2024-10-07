//
// Created by 回忆 on 24-10-4.
//

#ifndef HYWINDOW_BUILDER_H
#define HYWINDOW_BUILDER_H

#include <HYGUI/HYColor.h>
#include <HYGUI/HYDefine.h>
#include <HYGUI/HYTypeDef.h>

namespace HYGUI {
class HYWindow;

class HYWindowBuilder final : public HYClassBase {
  std::shared_ptr<HYWindow> m_window;

public:
  explicit HYWindowBuilder(const HYString &title = "");
  ~HYWindowBuilder() override;

  HYWindowBuilder &X(int x);
  HYWindowBuilder &Y(int y);
  HYWindowBuilder &Point(int x, int y);
  HYWindowBuilder &Width(int width);
  HYWindowBuilder &Height(int height);
  HYWindowBuilder &Size(int width, int height);
  HYWindowBuilder &Rect(int x, int y, int width, int height);
  HYWindowBuilder &Title(const HYString &title);

  HYWindowBuilder &BackGroundColor(const HYRGB&color);


  [[nodiscard]] HYWindow* Build() const;
};

}// namespace HYGUI

#endif//WINDOW_BUILDER_H
