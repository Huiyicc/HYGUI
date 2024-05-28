//
// Created by 19254 on 24-5-28.
//
#include <HYGUI/Helper/Encode.h>
#include <string>

#ifdef _HOST_WINDOWS_

#include <windows.h>

#else
#error "Unsupported platform"
#endif

namespace HYGUI {

wchar_t *HYA2W(const char *ansiStr, int CodePage) {
  #ifdef _HOST_WINDOWS_
  CodePage = CodePage == 0 ? 936 : CodePage;
  int wcharCount = MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, nullptr, 0); // 获取需要的缓冲区大小
  if (wcharCount == 0) {
    return nullptr;
  }
  auto wideStr = new wchar_t[wcharCount];
  int result = MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, wideStr, wcharCount);
  if (result == 0) {
    delete[] wideStr;
    return nullptr;
  }
  return wideStr;
  #else
  #error "Unsupported platform"
  #endif
}

}
