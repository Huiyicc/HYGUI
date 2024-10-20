//
// Created by 19254 on 24-10-20.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYWidget.h>
#include <HYGUI/HYWindow.h>
#include <SDL3/SDL.h>

namespace HYGUI {

void _widget_call_(HYWindow *window, HYWidget *widget, HYWidgetEvent event, int64_t param1, int64_t param2) {
  if (window) {
    for (auto w: window->m_children) {
      if (w == widget) {
        w->eventHandle(window, widget, event, param1, param2);
        return;
      }
    }
  }
  for (auto w: widget->m_children) {
    if (w == widget) {
      w->eventHandle(window == nullptr ? widget->m_window : window, widget, event, param1, param2);
      return;
    }
    for (auto wc: widget->m_children) {
      _widget_call_(nullptr, widget, event, param1, param2);
    }
  }
}

void HYObjectPushEvent(HYWindow *window, HYWidget *widget, HYWidgetEvent event, int64_t param1, int64_t param2) {
  SDL_Event e;
  auto &l = g_app;
  e.type = g_app.EventObject;
  e.user.windowID = window->ID();
  e.user.code = (SDL_EventType) event;
  e.user.timestamp = SDL_GetTicksNS();
  auto ts = (uint64_t *) malloc(sizeof(uint64_t) * 3);
  ts[0] = uint64_t(widget);
  ts[1] = param1;
  ts[2] = param2;
  e.user.data1 = ts;
  e.user.data2 = nullptr;
  SDL_PushEvent(&e);
}

}// namespace HYGUI