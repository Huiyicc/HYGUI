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
  std::vector<std::string> infos = {
    "为我推荐",
    "云音乐精选",
    "博客",
    "私人漫游",
    "社区",
  };

  for (int i = 0; i < infos.size(); i++) {
    auto t_label = HYGUI::HYLabelCreate(window, f_label, infos[i].c_str(), 24, 90+(i*(36+5)), 156, 36);
    HYLabelSetColorStyle(t_label,
                         HYGradientMode::HYGradientModeLinear,
                         HYGradientDirection::HYGradientDirectionLeftToRight,
                         {HYColorGenARGB(252, 59, 91),HYColorGenARGB(252, 61, 73)},
                         HYColorGenARGB(78, 86, 105),
                         HYColorGenARGB(80, 89, 107),
                         0);
  }


  //252, 59, 91
}