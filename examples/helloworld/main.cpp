//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>


int main() {
  HYGUI::HYInit(nullptr,0);
  auto wind = HYGUI::HYWindowCreate(nullptr, "Hello World", 100, 100, 400, 400);
  HYGUI::HYWindowShow(wind);
  HYGUI::HYWindowMessageLoop(wind);

  return 0;
}