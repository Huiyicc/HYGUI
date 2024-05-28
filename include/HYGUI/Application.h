//
// Created by 19254 on 24-5-27.
//

#ifndef HYGUI_APPLICATION_H
#define HYGUI_APPLICATION_H

#include <mutex>
#include <vector>

namespace HYGUI {

struct HY_ApplicationInfo {
  intptr_t hModuleUser;
  intptr_t hInstance;
  int dwFlags;
  intptr_t csError;
  int dwError;
  void* hCursor;
  void* hIcon;
  void* hIconsm;
  float_t DpiX;
  float_t DpiY;
  float_t DpiX_Real;
  float_t DpiY_Real;
  uint16_t atomClassName;
  uint16_t atomSysShadow;
  uint32_t dwMessage;
  void *hMemPoolMsg;
  void *hTableClass;
  void *hTableFont;
  void *hTableLayout;
  void *pfnUpdateLayeredWindowIndirect;
  intptr_t lpLogFontDefault;
  intptr_t hThemeDefault;
  intptr_t hMenuVS;
  intptr_t hMenuHS;
  intptr_t hMenuEdit;
  intptr_t hHookMsgBox;
  void *hHandles;
  std::vector<void*> aryThemes;
  std::vector<int32_t > aryColorsAtom;
  std::vector<int32_t> aryColorsOffset;
  const wchar_t * lpStrMin;
  const wchar_t * lpStrResMin;
  const wchar_t * lpStrMax;
  const wchar_t * lpStrResMax;
  const wchar_t * lpStrClose;
  const wchar_t * lpStrHelp;
  uint32_t dwClickTime;
  void *fContext;
};

bool HYInit(intptr_t hInstance,
            uint32_t dwGlobalFlags, // HYGF_*
            intptr_t hDefaultCursor, //默认鼠标指针
            intptr_t lpszDefaultClassName, //默认类名
            intptr_t lpDefaultTheme, //默认主题包指针
            intptr_t dwDefaultThemeLen, //默认主题包长度
            intptr_t lpDefaultI18N, //默认语言包指针
            intptr_t dwDefaultI18NLen //默认语言包长度
);

}

#endif //HYGUI_APPLICATION_H
