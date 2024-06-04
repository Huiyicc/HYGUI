//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>

using namespace HYGUI;


int main() {
  HYInit(nullptr, HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind,HYRGB{255,255,255},210);

  auto label = CreateLabel(wind,nullptr,L"Hello World", 10, 10, 100, 100);

  HYWindowShow(wind);
  HYWindowMessageLoop(wind);

  return 0;
}