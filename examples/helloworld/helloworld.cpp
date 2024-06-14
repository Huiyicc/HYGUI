//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>

using namespace HYGUI;


int main() {

  #ifdef _WIN32
  system("chcp 65001");
  #endif

  HYInit(nullptr, HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind,HYRGB{255,255,255},210);

  auto label = HYLabelCreate(wind,nullptr,"Hello World", 50, 50, 700, 500);
  HYLabelSetBackgroundColor(label,HYARGB{255,0,255,0});
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label),"标签绿");

  auto label1 = HYLabelCreate(wind,label,"Hello World", 200, 160, 300, 250);
  HYLabelSetBackgroundColor(label1,HYARGB{255,0,0,255});
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label1),"标签蓝");

  auto label11 = HYLabelCreate(wind,label1,"Hello World", -120, -80, 300, 150);
  HYLabelSetBackgroundColor(label11,HYARGB{255,255,0,0});
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label11),"标签红");


  HYWindowShow(wind);
  HYWindowMessageLoop(wind);

  return 0;
}


