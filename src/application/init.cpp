//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/core/application.h>
#include <HYGUI/core/window.h>
#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif


namespace HYGUI {

void HInit() {
#ifdef _HOST_WINDOWS_
  CoInitialize(nullptr);
  HRegisterWindowClass(WINDOWCLASSNAME);
#else
  #error "Not implemented"
#endif
}

}