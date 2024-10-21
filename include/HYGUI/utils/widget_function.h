//
// Created by 19254 on 24-10-20.
//

#ifndef HYGUI_WIDGET_FUNCTION_H
#define HYGUI_WIDGET_FUNCTION_H

union SDL_Event;

namespace HYGUI {

#ifdef _HYGUI_MODULE_

void _widget_call_(HYWindow *window, HYWidget *widget, HYWidgetEvent event, int64_t param1, int64_t param2);

#endif

void HYObjectPushEvent(HYWindow *window, HYWidget* widget, HYWidgetEvent event, int64_t param1, int64_t param2);

}

#endif//HYGUI_WIDGET_FUNCTION_H
