//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_PRIVATEDEFINITION_H
#define HYGUI_PRIVATEDEFINITION_H

#include <HYGUI/Application.h>
#include <HYGUI/Window.h>


#ifdef _HOST_WINDOWS_
#include <windows.h>
#include <ocidl.h>
#include <olectl.h>
#include <atlbase.h>
#include <atlwin.h>
#else
#error "Unsupported platform"
#endif


namespace HYGUI {

extern ApplicationInfo g_app;

constexpr const wchar_t *DEFAULT_CLASS_NAME = L"HYGUI";

void window_paint(HYWindow *windowPtr, HWND hWnd);
void window_recreate_surface(HYWindow *windowPtr);
int processing_object_event(HYObjectEventQueue*queue, HYObjectEventInfo&event_info);


}

#include "logs.h"

#endif //HYGUI_PRIVATEDEFINITION_H
