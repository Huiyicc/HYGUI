//
// Created by 19254 on 24-7-20.
//
#include <HYGUI/HYGUI.h>
#include <format>
#include <iostream>
#include <random>

using namespace HYGUI;

bool random_bool() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  return dis(gen) == 1;
}


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
  std::cout << std::format("左键按下1(键状态:{})", (int) keymode) << std::endl;
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

int onLeftUp(HYWindow *w, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "左键弹起" << std::endl;
  HYWindowDestroy(w);
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

int onMiddleDown(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "中键按下" << std::endl;
  return 0;
}

int onMiddleUp(HYWindow *, HYObject *, int, int, HYKeymod keymode) {
  std::cout << "中键弹起" << std::endl;
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

int mouseWheel(HYWindow *, HYObject *, float x, float y, HYKeymod keymode) {
  std::cout << std::format("鼠标滚轮移动:[{},{}]({})", x, y, keymode) << std::endl;
  return 0;
}

int keyDown(HYWindow *, HYObject *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("键盘按下: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}", KeyboardID, (uint32_t) Scancode, KeyCode, Keymod) << std::endl;
  return 0;
}

int keyUp(HYWindow *, HYObject *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("键盘抬起: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}", KeyboardID, (uint32_t) Scancode, KeyCode, Keymod) << std::endl;
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

void windowCreate(HYWindow *) {
  std::cout << "窗口创建" << std::endl;
}

void windowPaint(HYWindow *, CanvasPtr canvas, PaintPtr paint, HYRect *) {
  std::cout << "窗口背景重绘" << std::endl;
  HYPaintSetColor(paint, HYARGB{255, 190, 249, 129});
  HYRect r = {10, 50, 30, 30};
  HYPaintDrawRect(canvas, paint, &r);
}

bool beforeClose(HYWindow *) {
  auto c = random_bool();
  if (c) {
    std::cout << "窗口允许关闭" << std::endl;
  } else {
    std::cout << "窗口不允许关闭" << std::endl;
  }
  return c;
}

void willDestroy(HYWindow *) {
  std::cout << "窗口将要销毁" << std::endl;
}

void windowMove(HYWindow *, HYPoint *pNew) {
  // std::cout << std::format("窗口移动,新:[{},{}]",  pNew->x, pNew->y) << std::endl;
}

void windowResize(HYWindow *, HYRect *pNew) {
  // std::cout << std::format("窗口大小改变,新:[{},{}]",  pNew->width, pNew->height) << std::endl;
}

void windowActivate(HYWindow *) {
  std::cout << "窗口激活" << std::endl;
}

void windowDeactivate(HYWindow *) {
  std::cout << "窗口取消激活" << std::endl;
}

void windowFirstActivate(HYWindow *) {
  std::cout << "窗口首次激活" << std::endl;
}

void windowFocusGained(HYWindow *) {
  std::cout << "窗口获得焦点" << std::endl;
}

void windowFocusLost(HYWindow *) {
  std::cout << "窗口取消焦点" << std::endl;
}

void windowMouseLeave(HYWindow *) {
  std::cout << "窗口鼠标退出" << std::endl;
}

void windowMouseEnter(HYWindow *) {
  std::cout << "窗口鼠标进入" << std::endl;
}

void windowShow(HYWindow *) {
  std::cout << "窗口显示" << std::endl;
}

void windowHide(HYWindow *) {
  std::cout << "窗口隐藏" << std::endl;
}

void windowLeftUp(HYWindow *, int, int, HYKeymod keymode) {
  std::cout << "窗口左键弹起" << std::endl;
}

void windowLeftDown(HYWindow *, int, int, HYKeymod keymode) {
  std::cout << "窗口左键按下" << std::endl;
}

void windowMiddleUp(HYWindow *, int, int, HYKeymod keymode) {
  std::cout << "窗口中键弹起" << std::endl;
}

void windowMiddleDown(HYWindow *, int, int, HYKeymod keymode) {
  std::cout << "窗口中键按下" << std::endl;
}

void windowRightUp(HYWindow *, int, int, HYKeymod keymode) {
  std::cout << "窗口右键弹起" << std::endl;
}

void windowRightDown(HYWindow *, int, int, HYKeymod keymode) {
  std::cout << "窗口右键按下" << std::endl;
}

void windowMouseMove(HYWindow *, int x, int y, HYKeymod keymode) {
  // std::cout << "窗口鼠标移动" << std::endl;
}

void windowMouseWheel(HYWindow *, float x, float y, HYKeymod keymode) {
  std::cout << std::format("窗口鼠标滚轮滚动:[{},{}]({})", x, y, keymode) << std::endl;
}


int windowKeyDown(HYWindow *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("窗口键按下: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}", KeyboardID, (uint32_t) Scancode, KeyCode, Keymod) << std::endl;
  return 0;
}

int windowKeyUp(HYWindow *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("窗口键抬起: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}", KeyboardID, (uint32_t) Scancode, KeyCode, Keymod) << std::endl;
  return 0;
}

#include <cuchar>

int main() {

#ifdef _WIN32
  system("chcp 65001");
#endif

  HYString aa("好好21");
  aa.forEachUtf8CharBoundary([](size_t start,size_t len) {
    std::cout << std::format("start:{},len:{}", start, len) << std::endl;
  });

  HYInit(HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind, HYRGB{255, 255, 255}, 210);

  wind->RegisterEventCreateCallback(windowCreate);
  wind->RegisterEventBackgroundPaintCallback(windowPaint);
  wind->RegisterEventBeforeCloseCallback(beforeClose);
  wind->RegisterEventWillDestroyCallback(willDestroy);
  wind->RegisterEventMoveCallback(windowMove);
  wind->RegisterEventResizeCallback(windowResize);
  wind->RegisterEventFirstActivateCallback(windowFirstActivate);
  wind->RegisterEventFocusGainedCallback(windowFocusGained);
  wind->RegisterEventFocusLostCallback(windowFocusLost);
  wind->RegisterEventShowCallback(windowShow);
  wind->RegisterEventHideCallback(windowHide);
  wind->RegisterEventLeftUpCallback(windowLeftUp);
  wind->RegisterEventLeftDownCallback(windowLeftDown);
  wind->RegisterEventMiddleUpCallback(windowMiddleUp);
  wind->RegisterEventMiddleDownCallback(windowMiddleDown);
  wind->RegisterEventRightUpCallback(windowRightUp);
  wind->RegisterEventRightDownCallback(windowRightDown);
  wind->RegisterEventMouseLeaveCallback(windowMouseLeave);
  wind->RegisterEventMouseEnterCallback(windowMouseEnter);
  wind->RegisterEventMouseMoveCallback(windowMouseMove);
  wind->RegisterEventMouseWheelCallback(windowMouseWheel);
  wind->RegisterEventKeyUpCallback(windowKeyUp);
  wind->RegisterEventKeyDownCallback(windowKeyDown);


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
  label->RegisterEventMiddleDownCallback(onMiddleDown);
  label->RegisterEventMiddleUpCallback(onMiddleUp);
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
  HYExit();
  return 0;
}
