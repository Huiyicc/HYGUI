//
// Created by 19254 on 24-10-21.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYWidget.h>
#include <HYGUI/HYWindow.h>
#include <map>

namespace HYGUI {

int HYWidgetHelpers::eventHandel(HYGUI::HYWindow *window, HYGUI::HYWidget *widget, HYGUI::HYWidgetEvent event, int64_t p1, int64_t p2) {
  return widget->MessageEvent(event, p1, p2);
}

int HYWidgetHelpers::repaint(HYGUI::HYWindow *window, HYGUI::HYWidget *widget, HYGUI::HYWidgetEvent event, int64_t p1, int64_t p2) {
  if (!(widget && window)) {
    return 0;
  }
  widget->Events.OnPaint(window, widget);
  return 0;
}

std::map<HYWidgetEvent, std::function<int(HYWindow *, HYWidget *, HYWidgetEvent, int64_t, int64_t)>> g_widget_event = {
  {HYWidgetEvent::HYWidgetEvent_Event, HYWidgetHelpers::eventHandel},
  {HYWidgetEvent::HYWidgetEvent_Paint, HYWidgetHelpers::repaint},
};

}// namespace HYGUI