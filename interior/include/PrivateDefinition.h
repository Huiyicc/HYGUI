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
#else
#error "Unsupported platform"
#endif


namespace HYGUI {

extern ApplicationInfo g_app;

constexpr const wchar_t *DEFAULT_CLASS_NAME = L"HYGUI";



}

#include "logs.h"

#endif //HYGUI_PRIVATEDEFINITION_H
