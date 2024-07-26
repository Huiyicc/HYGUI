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
  // std::cout << std::format("event:{}",(int)event) << std::endl;
  return 0;
}

void onCreate(HYWindow *, HYObject *) {
  std::cout << "创建事件" << std::endl;
}
int onLeftDown1(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << std::format("左键按下1(键状态:{})",(int)keymode) << std::endl;
  return 0;
}
int onLeftDown2(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "左键按下2 - 拦截后续" << std::endl;
  return 1;
}

int onLeftDown3(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "左键按下3 - 无效" << std::endl;
  return 0;
}

int onLeftUp(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "左键弹起" << std::endl;
  return 0;
}

int onRightDown(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "右键按下" << std::endl;
  return 0;
}

int onRightUp(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "右键弹起" << std::endl;
  return 0;
}

int mouseMove(HYWindow *, HYObject *, int x, int y, HYKeymod keymode) {
  // std::cout << std::format("鼠标移动:[{},{}]({})",x,y,status) << std::endl;
  return 0;
}

int mouseEnter(HYWindow *, HYObject *) {
  std::cout << std::format("鼠标进入") << std::endl;
  return 0;
}

int mouseLeave(HYWindow *, HYObject *) {
  std::cout << std::format("鼠标退出") << std::endl;
  return 0;
}

int mouseWheel(HYWindow *, HYObject *,float x,float y,HYKeymod keymode) {
  std::cout << std::format("鼠标滚轮移动:[{},{}]({})",x,y,keymode) << std::endl;
  return 0;
}

int keyDown(HYWindow *, HYObject *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("键盘按下: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}",KeyboardID,(uint32_t)Scancode,KeyCode,Keymod) << std::endl;
  return 0;
}

int keyUp(HYWindow *, HYObject *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("键盘抬起: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}",KeyboardID,(uint32_t)Scancode,KeyCode,Keymod) << std::endl;
  return 0;
}

void isShow(HYWindow *, HYObject *) {
  std::cout << "显示事件" << std::endl;
}

void focusGained(HYWindow *, HYObject *) {
  std::cout << "获得焦点" << std::endl;
}

void focusLost(HYWindow *, HYObject *) {
  std::cout << "失去焦点" << std::endl;
}

int main() {

#ifdef _WIN32
  system("chcp 65001");
#endif

  HYInit(HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind, HYRGB{255, 255, 255}, 210);

  auto label = HYLabelCreate(wind, nullptr, "标签1\n\ncascas", 50, 50, 700, 500, true, event);
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
  label->RegisterEventLeftUpCallback(onLeftUp);
  label->RegisterEventRightDownCallback(onRightDown);
  label->RegisterEventRightUpCallback(onRightUp);
  label->RegisterEventMouseMoveCallback(mouseMove);
  label->RegisterEventShowCallback(isShow);
  label->RegisterEventMouseEnterCallback(mouseEnter);
  label->RegisterEventMouseLeaveCallback(mouseLeave);
  label->RegisterEventMouseWheelCallback(mouseWheel);
  label->RegisterEventFocusGainedCallback(focusGained);
  label->RegisterEventFocusLostCallback(focusLost);
  label->RegisterEventKeyDownCallback(keyDown);
  label->RegisterEventKeyUpCallback(keyUp);

  auto label1 = HYLabelCreate(wind, label, u8"标签2\n\n2132", 200, 160, 300, 250, true);
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
