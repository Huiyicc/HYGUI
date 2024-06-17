//
// Created by 回忆 on 24-6-17.
//
#include <QuartzCore/QuartzCore.h>
#import "Cocoa/Cocoa.h"
#include <SDL2/SDL_syswm.h>

namespace HYGUI {

void adjust_win_tyle(SDL_SysWMinfo* wmInfo) {
  NSWindow *nswindow = wmInfo->info.cocoa.window;

  // 去掉窗口装饰
  [nswindow setStyleMask:NSWindowStyleMaskBorderless];

  // 强制更新窗口样式
  [nswindow makeKeyAndOrderFront:nil];
  [nswindow display];

}

}