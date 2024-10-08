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
#include "SDL3/SDL.h"

struct SDL_SysWMinfo;

namespace HYGUI {

extern ApplicationInfo g_app;

constexpr const char *const DEFAULT_CLASS_NAME = "HYGUI";
extern const std::unordered_map<char32_t, std::tuple<const char*,const char *>> g_emoji_map;

void window_paint(HYWindow *, void *) ;
void window_recreate_surface(HYWindow *windowPtr);
//int processing_object_event(HYObjectEventQueue*queue, HYObjectEventInfo&event_info);
int _obj_event(HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2);
void adjustwindow_by_sdl(HYWindowHandel window , void *newhandel);
void adjust_win_tyle(SDL_SysWMinfo* wmInfo);
void window_hook_handel(HYWindow *windowPtr);



}

#include "logs.h"
#include "ResourceManage.h"

#endif //HYGUI_PRIVATEDEFINITION_H
