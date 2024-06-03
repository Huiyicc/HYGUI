//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>


int main() {
  HYGUI::HYInit(nullptr, HYGUI::HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYGUI::HYWindowCreate(nullptr, "Hello World", 100, 100, 400, 400);
  HYWindowSkinHook(wind);

  HYGUI::HYWindowShow(wind);
  HYGUI::HYWindowMessageLoop(wind);

  return 0;
}