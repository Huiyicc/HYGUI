//
// Created by 19254 on 24-5-31.
//
#include "HYGUI/Coding.h"
#include "PrivateDefinition.h"

namespace HYGUI {

wchar_t *C2W_(const char *str) {
  #ifdef _HOST_WINDOWS_
  int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
  auto wstr = new wchar_t[len];
  MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, len);
  return wstr;
  #else
  #error "Unsupported platform"
  #endif
}

char *W2C_(const wchar_t *str) {
  #ifdef _HOST_WINDOWS_
  int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
  auto cstr = new char[len];
  WideCharToMultiByte(CP_ACP, 0, str, -1, cstr, len, NULL, NULL);
  return cstr;
  #else
  #error "Unsupported platform"
  #endif
}

}