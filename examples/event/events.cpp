//
// Created by 19254 on 24-7-20.
//
#include <HYGUI/HYGUI.h>
#include <format>
#include <iostream>

using namespace HYGUI;


int event(HYWindow *window, HYObject *obj, HYObjectEvent event, uint64_t p1, uint32_t p2) {
  // std::cout << std::format("wind:{},obj:{},event:{},p1:{},p2:{}",(uintptr_t )window,(uintptr_t )obj,(int32_t )event,p1,p2) << std::endl;
  if (event == HYObjectEvent::HYObjectEvent_Create) {
    // 由于架构设计原因,创建事件只能由此派发
    std::cout << "组件创建" << std::endl;
  }
  return 0;
}

void onCreate(HYWindow *, HYObject *) {
  std::cout << "创建事件" << std::endl;
}
int onLeftDown1(HYWindow *, HYObject *, int, int, int) {
  std::cout << "左键按下1" << std::endl;
  return 0;
}
int onLeftDown2(HYWindow *, HYObject *, int, int, int) {
  std::cout << "左键按下2 - 拦截后续" << std::endl;
  return 1;
}

int onLeftDown3(HYWindow *, HYObject *, int, int, int) {
  std::cout << "左键按下3 - 无效" << std::endl;
  return 0;
}


int main() {

#ifdef _WIN32
  system("chcp 65001");
#endif

  HYInit(nullptr, HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind, HYRGB{255, 255, 255}, 210);

  auto label = HYLabelCreate(wind, nullptr, "标签1\n\ncascas", 50, 50, 700, 500, event);
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

  auto label1 = HYLabelCreate(wind, label, u8"标签2\n\n2132", 200, 160, 300, 250);
  HYLabelSetColorStyle(label1, HYGradientMode::HYGradientModeRadial,
                       HYGradientDirection::HYGradientDirectionTopLeftToBottomRight,
                       {HYARGB{255, 0, 0, 255}, HYARGB{255, 255, 0, 0}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 255, 0, 0}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label1), "标签2 b");

  HYWindowShow(wind);
  HYWindowMessageLoop();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  HYExit();
  return 0;
}
