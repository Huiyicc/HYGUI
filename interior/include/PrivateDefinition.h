//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_PRIVATEDEFINITION_H
#define HYGUI_PRIVATEDEFINITION_H

#include <HYGUI/Application.h>
#include <HYGUI/Window.h>
#include <HYGUI/Helper/Encode.h>
#include <HYGUI/Helper/Data.h>

#ifdef _HOST_WINDOWS_
#include <windows.h>
#include <ocidl.h>
#include <olectl.h>
#else
#error "Unsupported platform"
#endif

#define PtrForceToIntptr(x) (intptr_t)((void*)(x))

namespace HYGUI {

extern HY_ApplicationInfo g_Li;

constexpr const wchar_t *DEFAULT_CLASS_NAME = L"HYGUI";
constexpr const char *DEFAULT_CLASS_NAMEA = "HYGUI";


void pfnDefaultFreeData(LPVOID dwData);

}

#endif //HYGUI_PRIVATEDEFINITION_H
