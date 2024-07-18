//
// Created by 19254 on 24-7-2.
//
#include <HYGUI/HYGUI.h>
#include <iostream>
#include "layout.h"

using namespace HYGUI;

int main() {
  HYInit(nullptr, HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "cloud music",WINDOWCREATEPOINT_USEDEFAULT, WINDOWCREATEPOINT_USEDEFAULT, 1057, 752);
  HYWindowSkinHook(wind, HYRGB{247, 249, 252}, 255,10);

  layout_left(wind);

  HYWindowShow(wind);

  HYWindowMessageLoop();
  HYExit();
}