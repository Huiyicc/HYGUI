//
// Created by 19254 on 24-7-20.
//
#include <HYGUI/HYGUI.h>
#include <iostream>

using namespace HYGUI;

void onCreate(HYWindow *, HYObject *) {
  std::cout << "create" << std::endl;
}
int onLeftDown1(HYWindow *, HYObject *, int, int, int) {
  std::cout << "LeftDown1" << std::endl;
  return 0;
}
int onLeftDown2(HYWindow *, HYObject *, int, int, int) {
  std::cout << "LeftDown2 - 拦截" << std::endl;
  return 1;
}

int onLeftDown3(HYWindow *, HYObject *, int, int, int) {
  std::cout << "LeftDown3 - 无效" << std::endl;
  return 0;
}


int main() {

#ifdef _WIN32
  system("chcp 65001");
#endif

  HYInit(nullptr, HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind, HYRGB{255, 255, 255}, 210);

  auto label = HYLabelCreate(wind, nullptr, "标签1\n\ncascas", 50, 50, 700, 500);
  HYLabelSetColorStyle(label, HYGradientMode::HYGradientModeRadial,
                       HYGradientDirection::HYGradientDirectionTopToBottom,
                       {HYARGB{255, 0, 255, 0}, HYARGB{255, 0, 0, 255}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 0, 0, 255}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label), "标签1 g");
  label->RegisterEventCreateCallback(onCreate);
  label->RegisterEventLeftDownCallback(onLeftDown1);
  label->RegisterEventLeftDownCallback(onLeftDown2);
  label->RegisterEventLeftDownCallback(onLeftDown3);

  HYWindowShow(wind);
  HYWindowMessageLoop();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  HYExit();
  return 0;
}
