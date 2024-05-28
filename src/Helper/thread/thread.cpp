//
// Created by 19254 on 24-5-28.
//
#include <HYGUI/HYGUI.h>
#include <PrivateDefinition.h>

namespace HYGUI {

void *HY_Thread_InitializeCriticalSection() {
  #ifdef _HOST_WINDOWS_
  auto addr = LocalAlloc(64, sizeof(CRITICAL_SECTION));
  InitializeCriticalSection((LPCRITICAL_SECTION) addr);
  return addr;
  #else
  #error "Unsupported platform"
  #endif

}

}