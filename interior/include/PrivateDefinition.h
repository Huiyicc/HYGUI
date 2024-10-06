//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_PRIVATEDEFINITION_H
#define HYGUI_PRIVATEDEFINITION_H

#include "HYGUI/HYException.h"
#ifdef _HOST_WINDOWS_
#include <atlbase.h>
#include <atlwin.h>
#include <ocidl.h>
#include <olectl.h>
#include <windows.h>
#elif defined(_HOST_APPLE_)
#elif defined(_HOST_LINUX_)

#else
#error "Unsupported platform"
#endif
#include <HYGUI/HYApplication.h>
//#include <HYGUI/Window.h>
#include "Defer.h"
#include "SDL3/SDL.h"

struct SDL_SysWMinfo;

namespace HYGUI {

extern ApplicationInfo g_app;

constexpr const char *const DEFAULT_CLASS_NAME = "HYGUI";
extern const std::unordered_map<char32_t, std::tuple<const char *, const char *>> g_emoji_map;

//void window_paint(HYWindow *, void *) ;
//void window_recreate_surface(HYWindow *windowPtr);
////int processing_object_event(HYObjectEventQueue*queue, HYObjectEventInfo&event_info);
//int _obj_event(HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2);
//void adjustwindow_by_sdl(HYWindowHandel window , void *newhandel);
void adjust_win_tyle(SDL_SysWMinfo *wmInfo);
void window_hook_handel(HYWindow *windowPtr);

int _window_event_handel(HYWindow *window, SDL_Event *event);

template<typename T>
struct HYPtrDeleter {
  void operator()(T *ptr) {
    if (ptr) {
      ptr->unref();
    }
  }
};

}// namespace HYGUI

#include "ResourceManage.h"
#include "logs.h"

#define HYGUICLASS_SRC_DEFINE(CLASSTYPE, PKGTYPE)        \
  bool CLASSTYPE::operator==(const nullptr_t &p) const { \
    return m_ptr == p;                                   \
  }                                                      \
  PKGTYPE *CLASSTYPE::operator->() const {               \
    return m_ptr.get();                                  \
  };                                                     \
  PKGTYPE *CLASSTYPE::get() const {                      \
    return m_ptr.get();                                  \
  };                                                     \
  bool CLASSTYPE::operator!() const {                    \
    return !m_ptr;                                       \
  };                                                     \
  CLASSTYPE::operator bool() const {                     \
    return m_ptr!=nullptr;                                        \
  }

#endif//HYGUI_PRIVATEDEFINITION_H
