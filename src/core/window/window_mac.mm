//
// Created by 回忆 on 24-10-4.
//
#include <QuartzCore/QuartzCore.h>
#import "Cocoa/Cocoa.h"
#include <SDL3/SDL_system.h>
#include <HYGUI/HYWindow.h>
#include<SDL3/SDL_properties.h>
#include<SDL3/SDL_video.h>

namespace HYGUI {

#if defined(_HOST_APPLE_)
WindowHandelInfo HYWindow::GetHandel() const {
    NSWindow *nswindow = (__bridge NSWindow *) SDL_GetPropertyType(SDL_GetWindowProperties(m_SDLWindow), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER);
//  if (nswindow) {
//
//  }
    return {nswindow};
}
#endif

void adjust_win_tyle(WindowHandelInfo* wmInfo) {
  auto nswindow = (NSWindow *)wmInfo->handle;

  // 去掉窗口装饰
  [nswindow setStyleMask:NSWindowStyleMaskBorderless];

  // 强制更新窗口样式
  [nswindow makeKeyAndOrderFront:nil];
  [nswindow display];

}

 }