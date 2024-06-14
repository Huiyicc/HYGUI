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

#else
#error "Unsupported platform"
#endif
#include <HYGUI/Application.h>
#include <HYGUI/Window.h>



namespace HYGUI {

extern ApplicationInfo g_app;

constexpr const wchar_t *DEFAULT_CLASS_NAME = L"HYGUI";

void window_paint(HYWindow *windowPtr);
void window_recreate_surface(HYWindow *windowPtr);
int processing_object_event(HYObjectEventQueue*queue, HYObjectEventInfo&event_info);
// int _obj_paint(HYObject *obj, SkCanvas *canvas, SkPaint &paint, const HYRect &offset_point);
// int _obj_event(HYWindow *window, HYObject *obj, int event, int param1, int param2);
void _obj_event_list(HYWindow *window, HYObject *obj, int event, int param1, int param2);

}

#include "logs.h"

#endif //HYGUI_PRIVATEDEFINITION_H
