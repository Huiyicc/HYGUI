//
// Created by 19254 on 24-5-31.
//
#include "HYGUI/Coding.h"
#include "PrivateDefinition.h"

#ifdef _HOST_APPLE_

#include <unicode/unistr.h>
#include <unicode/ucnv.h>

#endif

namespace HYGUI {

wchar_t *C2W_(const char *str) {
  #ifdef _HOST_WINDOWS_
  int len = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
  auto wstr = new wchar_t[len];
  MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, len);
  return wstr;
  #elif defined(_HOST_APPLE_)
  auto unicodeString = icu::UnicodeString::fromUTF8(icu::StringPiece(str));

  auto wstr = new wchar_t[unicodeString.length() + 1];
  UErrorCode status = U_ZERO_ERROR;
  unicodeString.toUTF32(reinterpret_cast<UChar32 *>(wstr), unicodeString.length() + 1, status);

  return wstr;
  #else
  #error "Unsupported platform"
  #endif
}

char *W2C_(const wchar_t *wstr) {
  #ifdef _HOST_WINDOWS_
  int len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
  auto cstr = new char[len];
  WideCharToMultiByte(CP_ACP, 0, wstr, -1, cstr, len, nullptr, nullptr);
  return cstr;
  #elif defined(_HOST_APPLE_)
  auto unicodeString = icu::UnicodeString::fromUTF32(reinterpret_cast<const UChar32 *>(wstr), -1);

  std::string str;
  unicodeString.toUTF8String(str);
  auto cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  return cstr;

  #else
  #error "Unsupported platform"
  #endif
}

}