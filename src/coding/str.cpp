//
// Created by 19254 on 24-5-14.
//
#include <HYGUI/coding/str.h>

#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif

namespace HYGUI {

std::wstring HA2W(std::string_view str) {
  std::wstring wstr;
  wstr.resize(MultiByteToWideChar(CP_ACP, 0, str.data(), str.size(), nullptr, 0));
  MultiByteToWideChar(CP_ACP, 0, str.data(), str.size(), wstr.data(), wstr.size());
  return wstr;
}

}