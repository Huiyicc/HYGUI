//
// Created by 19254 on 24-7-20.
//
#include <HYGUI/HYGUI.h>
#include <HYGUI/Widgets/HYLabel.h>
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


int event(HYWindow *window, HYWidget *obj, HYWidgetEvent event, uint64_t p1, uint32_t p2) {
  // std::cout << std::format("wind:{},obj:{},event:{},p1:{},p2:{}",(uintptr_t )window,(uintptr_t )obj,(int32_t )event,p1,p2) << std::endl;
  if (event == HYWidgetEvent::HYWidgetEvent_Create) {
    // std::cout << "组件创建" << std::endl;
  }
  // std::cout << std::format("组件事件:{}",(int)event) << std::endl;
  return 0;
}

void onCreate(HYWindow *, HYWidget *) {
  std::cout << "组件创建事件" << std::endl;
}

int onPaint(HYWindow *, HYWidget *,HYCanvas* canvas,HYPaint* paint) {
  std::cout << "组件绘制事件" << std::endl;
  return 0;
}

int onLeftDown1(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << std::format("左键按下1(键状态:{})", (int) keymode) << std::endl;
  return 0;
}
int onLeftDown2(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "左键按下2 - 拦截后续" << std::endl;
  return 1;
}

int onLeftDown3(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "左键按下3 - 无效" << std::endl;
  return 0;
}

int onLeftUp(HYWindow *w, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "左键弹起" << std::endl;
  // HYWindowDestroy(w);
  return 0;
}

int onRightDown(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "右键按下" << std::endl;
  return 0;
}

int onRightUp(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "右键弹起" << std::endl;
  return 0;
}

int onMiddleDown(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "中键按下" << std::endl;
  return 0;
}

int onMiddleUp(HYWindow *, HYWidget *, int, int, HYKeymod keymode) {
  std::cout << "中键弹起" << std::endl;
  return 0;
}

int mouseMove(HYWindow *, HYWidget *, int x, int y, HYKeymod keymode) {
  // std::cout << std::format("鼠标移动:[{},{}]({})",x,y,status) << std::endl;
  return 0;
}

int mouseEnter(HYWindow *, HYWidget *) {
  std::cout << std::format("鼠标进入") << std::endl;
  return 0;
}

int mouseLeave(HYWindow *, HYWidget *) {
  std::cout << std::format("鼠标退出") << std::endl;
  return 0;
}

int mouseWheel(HYWindow *, HYWidget *, float x, float y, HYKeymod keymode) {
  std::cout << std::format("鼠标滚轮移动:[{},{}]({})", x, y, keymode) << std::endl;
  return 0;
}

int keyDown(HYWindow *, HYWidget *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("键盘按下: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}", KeyboardID, (uint32_t) Scancode, KeyCode, Keymod) << std::endl;
  return 0;
}

int keyUp(HYWindow *, HYWidget *, HYKeyboardID KeyboardID, HYScancode Scancode, HYKeyCode KeyCode, HYKeymod Keymod) {
  std::cout << std::format("键盘抬起: 键盘ID:{} 扫描码:{} 键代码:{} 修饰键:{}", KeyboardID, (uint32_t) Scancode, KeyCode, Keymod) << std::endl;
  return 0;
}

void isShow(HYWindow *, HYWidget *) {
  std::cout << "显示事件" << std::endl;
}

void focusGained(HYWindow *, HYWidget *) {
  std::cout << "获得焦点" << std::endl;
}

void focusLost(HYWindow *, HYWidget *) {
  std::cout << "失去焦点" << std::endl;
}

void windowCreate(HYWindow *) {
  std::cout << "窗口创建" << std::endl;
}

void windowPaint(HYWindow *, HYCanvas *canvas, HYPaint *paint, HYRect *) {
  std::cout << "窗口背景重绘" << std::endl;
  paint->SetColor({255, 190, 249, 129});
  canvas->DrawRect(*paint, {10, 50, 30, 30});
}

bool beforeClose(HYWindow *) {
  auto c = random_bool();
  if (c) {
    std::cout << "窗口不允许关闭" << std::endl;
  } else {
    std::cout << "窗口允许关闭" << std::endl;
  }
  return c;
}

void willDestroy(HYWindow *) {
  std::cout << "窗口将要销毁" << std::endl;
}

void windowMove(HYWindow *, HYPoint *pNew) {
  std::cout << std::format("窗口移动,新:[{},{}]", pNew->x, pNew->y) << std::endl;
}

void windowResize(HYWindow *, HYRect *pNew) {
  std::cout << std::format("窗口大小改变,新:[{},{}]", pNew->width, pNew->height) << std::endl;
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
  //   std::cout << "窗口鼠标移动" << std::endl;
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

  HYInit(HYGlobalFlag::HYGlobalFlagGraphicDefault);

  auto wind = HYWindowBuilder()
                .Size(800, 600)
                .Title("event test")
                .Build();
  /*
   wind->Events.OnCreate += windowCreate; √
   wind->Events.OnCreate.connect(windowCreate); √
   * */
  wind->Events.OnCreate.connect(windowCreate);
  wind->Events.OnBackgroundPaint.connect(windowPaint);
  wind->Events.OnBeforeClose.connect(beforeClose);
  //  wind->Events.OnWillDestroy.connect(willDestroy);
  wind->Events.OnMove.connect(windowMove);
  wind->Events.OnResize.connect(windowResize);
  wind->Events.OnFirstActivate.connect(windowFirstActivate);
  wind->Events.OnFocusGained.connect(windowFocusGained);
  wind->Events.OnFocusLost.connect(windowFocusLost);
  wind->Events.OnShown.connect(windowShow);
  wind->Events.OnHidden.connect(windowHide);
  wind->Events.OnLeftClickStart.connect(windowLeftDown);
  wind->Events.OnLeftClickEnd.connect(windowLeftUp);
  wind->Events.OnMiddleClickStart.connect(windowMiddleDown);
  wind->Events.OnMiddleClickEnd.connect(windowMiddleUp);
  wind->Events.OnRightClickStart.connect(windowRightDown);
  wind->Events.OnRightClickEnd.connect(windowRightUp);
  wind->Events.OnMouseLeave.connect(windowMouseLeave);
  wind->Events.OnMouseEnter.connect(windowMouseEnter);
  wind->Events.OnMouseMove.connect(windowMouseMove);
  wind->Events.OnMouseScroll.connect(windowMouseWheel);
  wind->Events.OnKeyPress.connect(windowKeyDown);
  wind->Events.OnKeyRelease.connect(windowKeyUp);


  auto obj1 = HYLabel::Make<HYLabel>()
                ->Point(10, 10)
                ->Size(100, 100);
  obj1->Events.OnEvent.connect(event);
  obj1->Events.OnCreate.connect(onCreate);

  obj1->Events.OnPaint.connect(onPaint);


  wind->AddWidget(obj1);

  wind->Show();
  HYRun();
  HYExit();



  // auto label = HYLabelCreate(wind, nullptr, "标签1\n\ncascas", 50, 50, 700, 500, true, event);
  // HYLabelSetColorStyle(label, HYGradientMode::HYGradientModeRadial,
  //                      HYGradientDirection::HYGradientDirectionTopToBottom,
  //                      {HYARGB{255, 0, 255, 0}, HYARGB{255, 0, 0, 255}},
  //                      HYARGB{255, 255, 255, 255},
  //                      HYARGB{255, 0, 0, 255}, 2);
  // HYObjectSetName(reinterpret_cast<HYObjectHandle>(label), "标签1 g");
  //
  // label->RegisterEventLeftDownCallback(onLeftDown1);
  // label->RegisterEventLeftDownCallback(onLeftDown2);
  // label->RegisterEventLeftDownCallback(onLeftDown3);
  // label->RegisterEventLeftUpCallback(onLeftUp);
  // label->RegisterEventRightDownCallback(onRightDown);
  // label->RegisterEventRightUpCallback(onRightUp);
  // label->RegisterEventMiddleDownCallback(onMiddleDown);
  // label->RegisterEventMiddleUpCallback(onMiddleUp);
  // label->RegisterEventMouseMoveCallback(mouseMove);
  // label->RegisterEventShowCallback(isShow);
  // label->RegisterEventMouseEnterCallback(mouseEnter);
  // label->RegisterEventMouseLeaveCallback(mouseLeave);
  // label->RegisterEventMouseWheelCallback(mouseWheel);
  // label->RegisterEventFocusGainedCallback(focusGained);
  // label->RegisterEventFocusLostCallback(focusLost);
  // label->RegisterEventKeyDownCallback(keyDown);
  // label->RegisterEventKeyUpCallback(keyUp);

  //  auto label1 = HYLabelCreate(wind, label, u8"标签2\n\n2132", 200, 160, 300, 250, true);
  //  HYLabelSetColorStyle(label1, HYGradientMode::HYGradientModeRadial,
  //                       HYGradientDirection::HYGradientDirectionTopLeftToBottomRight,
  //                       {HYARGB{255, 0, 0, 255}, HYARGB{255, 255, 0, 0}},
  //                       HYARGB{255, 255, 255, 255},
  //                       HYARGB{255, 255, 0, 0}, 2);
  //  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label1), "标签2 b");

  // HYWindowShow(wind);
  // HYWindowMessageLoop();
  // HYExit();

  return 0;
}
