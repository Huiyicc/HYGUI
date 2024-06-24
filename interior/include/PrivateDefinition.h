//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_PRIVATEDEFINITION_H
#define HYGUI_PRIVATEDEFINITION_H


#ifdef _HOST_WINDOWS_
#include <windows.h>
#include <ocidl.h>
#include <olectl.h>
#include <atlbase.h>
#include <atlwin.h>
#elif defined(_HOST_APPLE_)
#elif defined(_HOST_LINUX_)

#else
#error "Unsupported platform"
#endif
#include <HYGUI/Application.h>
#include <HYGUI/Window.h>
#include "Defer.h"
#include "SDL2/SDL.h"

struct SDL_SysWMinfo;

namespace HYGUI {

extern ApplicationInfo g_app;

constexpr const wchar_t *DEFAULT_CLASS_NAME = L"HYGUI";

void window_paint(HYWindow *, SDL_WindowEvent *) ;
void window_recreate_surface(HYWindow *windowPtr);
int processing_object_event(HYObjectEventQueue*queue, HYObjectEventInfo&event_info);
void adjustwindow_by_sdl(uint32_t id,SDL_Window *sdl_window,void*hwnd);
void adjust_win_tyle(SDL_SysWMinfo* wmInfo);

}

#include "logs.h"
#include "ResourceManage.h"

#endif //HYGUI_PRIVATEDEFINITION_H
