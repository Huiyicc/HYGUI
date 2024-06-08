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

  auto label = HYLabelCreate(wind,nullptr,"Hello World", 50, 50, 200, 200);
  HYLabelSetBackgroundColor(label,HYARGB{255,0,255,0}, true);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label),"标签绿");

  auto label_1 = HYLabelCreate(wind,label,"label", 10, 10, 180, 180);
  HYLabelSetBackgroundColor(label_1,HYARGB{255,255,0,0}, true);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label_1),"标签红");

  auto label_1_1 = HYLabelCreate(wind,label_1,"label", 5, 100, 180, 180);
  HYLabelSetBackgroundColor(label_1_1,HYARGB{255,255,120,0}, true);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label_1_1),"标签红_子");


  auto label_2 = HYLabelCreate(wind,label,"label", 150, 0, 30, 180);
  HYLabelSetBackgroundColor(label_2,HYARGB{255,0,0,255}, true);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label_2),"标签蓝");

  HYWindowShow(wind);
  HYWindowMessageLoop(wind);

  return 0;
}