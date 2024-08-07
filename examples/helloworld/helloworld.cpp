//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>
#include <iostream>

using namespace HYGUI;

int main() {

#ifdef _WIN32
  system("chcp 65001");
#endif

  HYInit(HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind, HYRGB{255, 255, 255}, 210);

  auto label = HYLabelCreate(wind, nullptr, "标签1\n\ncascas", 50, 50, 700, 500, true);
  HYLabelSetColorStyle(label, HYGradientMode::HYGradientModeRadial,
                       HYGradientDirection::HYGradientDirectionTopToBottom,
                       {HYARGB{255, 0, 255, 0}, HYARGB{255, 0, 0, 255}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 0, 0, 255}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label), "标签1 g");

  auto label1 = HYLabelCreate(wind, label, u8"标签2\n\n2132", 200, 160, 300, 250, true);
  HYLabelSetColorStyle(label1, HYGradientMode::HYGradientModeRadial,
                       HYGradientDirection::HYGradientDirectionTopLeftToBottomRight,
                       {HYARGB{255, 0, 0, 255}, HYARGB{255, 255, 0, 0}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 255, 0, 0}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label1), "标签2 b");

    auto label11 = HYLabelCreate(wind, label1, "标签红", -120, -80, 300, 150,true);
    HYLabelSetColorStyle(label11, HYGradientMode::HYGradientModeLinear,
                         HYGradientDirection::HYGradientDirectionTopLeftToBottomRight,
                         {HYARGB{255, 255, 0, 0}, HYARGB{255, 0, 255, 0}},
                         HYARGB{255, 255, 255, 255},
                         HYARGB{255, 0, 0, 255}, 2);
    HYObjectSetName(reinterpret_cast<HYObjectHandle>(label11), "标签红 r");

  HYWindowShow(wind);
  HYWindowMessageLoop();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  HYExit();
  return 0;
}
