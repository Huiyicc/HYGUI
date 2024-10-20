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
#include "Defer.h"
#include "SDL3/SDL.h"
#include <HYGUI/HYApplication.h>
#include <HYGUI/HYWidget.h>

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
void _widget_call_(HYWindow *window, HYWidget *widget, HYWidgetEvent event, int64_t param1, int64_t param2);

class HYWindowHelpers {
public:
  static void window_create(HYWindow *window, void *);
  static void window_will_destroy(HYWindow *, void *);
  static void window_resend_message(HYWindow *, void *);
  static void window_refresh(HYWindow *, void *);
  static int getMouseCursorType(HYWindow *window, int x, int y, int edge = 5);
  static int handleWindowsClose(SDL_Event *event, HYWindow *window);
  static int handleMouseButtonDown(SDL_Event *event, HYWindow *window);
  static int handleMouseButtonUp(SDL_Event *event, HYWindow *window);
  static int handleMouseMotion(SDL_Event *event, HYWindow *window);
  static int handleFocusGained(SDL_Event *event, HYWindow *window);
  static int handleFocusLost(SDL_Event *event, HYWindow *window);
  static int handleShown(SDL_Event *event, HYWindow *window);
  static int handleHidden(SDL_Event *event, HYWindow *window);
  static int handleMove(SDL_Event *event, HYWindow *window);
  static int handleSizeChanged(SDL_Event *event, HYWindow *window);
  static int handleMouseWheel(SDL_Event *event, HYWindow *window);
  static int handleKeyDown(SDL_Event *event, HYWindow *window);
  static int handleKeyUp(SDL_Event *event, HYWindow *window);
  static int _window_event_handel(HYWindow *window, SDL_Event *event);
};

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
    return m_ptr != nullptr;                             \
  }


#endif//HYGUI_PRIVATEDEFINITION_H
