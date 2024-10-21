//
// Created by 19254 on 24-10-20.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYWidget.h>
#include <HYGUI/HYWindow.h>
#include <SDL3/SDL.h>
#include <map>

namespace HYGUI {
extern std::map<HYWidgetEvent, std::function<int(HYWindow *, HYWidget *, HYWidgetEvent, uint64_t, uint32_t)>> g_widget_event;

void _widget_call_(HYWindow *window, HYWidget *widget, HYWidgetEvent event, int64_t param1, int64_t param2) {
  auto fcall = [](HYWindow *_window, HYWidget *_widget, HYWidgetEvent _event, int64_t _param1, int64_t _param2) {
    if (!_widget->m_init) {
      _widget->m_init = true;
      if (_widget->Events.OnEvent(_widget->m_window, _widget->m_parent, HYWidgetEvent::HYWidgetEvent_Create, 0, 0) == 0) {
        _widget->Events.OnCreate(_widget->m_window, _widget->m_parent);
      }
    }
    if (_window) {
      auto iter = g_widget_event.find(_event);
      if (iter != g_widget_event.end()) {
        iter->second(_window, _widget, _event, _param1, _param2);
      }
    }
  };
  if (window) {
    for (auto w: window->m_children) {
      if (w == widget) {
        fcall(window, widget, event, param1, param2);
        return;
      }
    }
  }
  for (auto w: widget->m_children) {
    if (w == widget) {
      fcall(window == nullptr ? widget->m_window : window, widget, event, param1, param2);
      return;
    }
    for (auto wc: widget->m_children) {
      _widget_call_(nullptr, wc, event, param1, param2);
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