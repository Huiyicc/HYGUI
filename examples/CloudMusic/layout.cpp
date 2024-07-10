//
// Created by 19254 on 24-7-4.
//
#include "layout.h"
#include "HYGUI/ObjectLabel.h"

using namespace HYGUI;

void layout_left(HYGUI::HYWindowHandel window) {
  auto f_label = HYGUI::HYLabelCreate(window, nullptr, "", 0, 0, 205, window->Height);
  HYLabelSetColorStyle(f_label,
                       HYGradientMode::HYGradientModeNone,
                       HYGradientDirection::HYGradientDirectionNone,
                       {HYColorGenARGB(240, 243, 246)},
                       HYColorGenARGB(80, 89, 107),
                       HYColorGenARGB(80, 89, 107),
                       0);

  //252, 59, 91
}