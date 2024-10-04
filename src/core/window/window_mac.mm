//
// Created by 回忆 on 24-10-4.
//
#import <Cocoa/Cocoa.h>
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
  }