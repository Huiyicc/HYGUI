//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>

using namespace HYGUI;


int main() {
  HYInit(nullptr, HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind,HYRGB{255,255,255},210);

  auto label = HYLabelCreate(wind,nullptr,L"Hello World", 50, 50, 100, 100);
  HYLabelSetBackgroundColor(label,HYARGB{255,0,255,0}, true);
  auto label_1 = HYLabelCreate(wind,label,L"label 1", 50, 50, 100, 100);
  HYLabelSetBackgroundColor(label_1,HYARGB{255,255,0,0}, true);
  auto label_2 = HYLabelCreate(wind,label,L"label 1", 5, 60, 90, 50);
  HYLabelSetBackgroundColor(label_2,HYARGB{120,0,0,255}, true);

  HYWindowShow(wind);
  HYWindowMessageLoop(wind);

  return 0;
}