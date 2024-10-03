//
// Created by 19254 on 24-5-31.
//
#include "HYGUI/HYCoding.h"
#include "PrivateDefinition.h"

#ifdef _HOST_APPLE_

#include <unicode/unistr.h>
#include <unicode/ucnv.h>
#elif defined(_HOST_LINUX_)
#include <iconv.h>
#include <cstring>
#include <cstdlib>
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
#elif defined(_HOST_LINUX_)
  iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
  if (cd == (iconv_t)-1) {
    return nullptr;
  }

  size_t inbytesleft = strlen(str) + 1;
  size_t outbytesleft = inbytesleft * sizeof(wchar_t);
  char *inbuf = const_cast<char*>(str);
  wchar_t *outbuf = new wchar_t[inbytesleft];
  char *outbuf_c = reinterpret_cast<char*>(outbuf);

  size_t result = iconv(cd, &inbuf, &inbytesleft, &outbuf_c, &outbytesleft);
  iconv_close(cd);

  if (result == (size_t)-1) {
    delete[] outbuf;
    return nullptr;
  }

  return outbuf;
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
#elif defined(_HOST_LINUX_)
  iconv_t cd = iconv_open("UTF-8", "WCHAR_T");
  if (cd == (iconv_t)-1) {
    return nullptr;
  }

  size_t inbytesleft = (wcslen(wstr) + 1) * sizeof(wchar_t);
  size_t outbytesleft = inbytesleft * sizeof(char);
  char *inbuf = reinterpret_cast<char*>(const_cast<wchar_t*>(wstr));
  char *outbuf = new char[outbytesleft];
  char *outbuf_c = outbuf;

  size_t result = iconv(cd, &inbuf, &inbytesleft, &outbuf_c, &outbytesleft);
  iconv_close(cd);

  if (result == (size_t)-1) {
    delete[] outbuf;
    return nullptr;
  }

  return outbuf;
#else
#error "Unsupported platform"
#endif
}
}
