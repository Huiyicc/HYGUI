//
// Created by 19254 on 24-5-28.
//
#include <PrivateDefinition.h>
#include <HYGUI/HYGUI.h>

#ifdef _HOST_WINDOWS_

#include <windows.h>


#else
#error "Unsupported platform"
#endif

namespace HYGUI {

// global application info
HY_ApplicationInfo g_Li = {0};

bool HY_Init(intptr_t hInstance,
             int dwGlobalFlags, // HYGF_*
            void *hDefaultCursor, //默认鼠标指针
            const wchar_t *lpszDefaultClassName, //默认类名
            void *lpDefaultTheme, //默认主题包指针
            size_t dwDefaultThemeLen, //默认主题包长度
            void * lpDefaultI18N, //默认语言包指针
            size_t dwDefaultI18NLen //默认语言包长度
) {
  #ifdef _HOST_WINDOWS_
  CoInitialize(nullptr);
  g_Li.csError = PtrForceToIntptr(HY_Thread_InitializeCriticalSection());

  g_Li.hInstance = hInstance;
  g_Li.dwFlags = dwGlobalFlags;
  if (hDefaultCursor == nullptr) {
    g_Li.hCursor = LoadCursorW(nullptr, (LPCWSTR)IDC_ARROW);
  } else {
    g_Li.hCursor = hDefaultCursor;
  }
  if (lpszDefaultClassName == nullptr) {
    lpszDefaultClassName = L"Ex_DirectUI";
  }

  wchar_t szFilePath[MAX_PATH + 1];
  GetModuleFileNameW(nullptr, szFilePath, MAX_PATH); //取自身完整路径

  g_Li.hIcon = ExtractIconW((HINSTANCE)g_Li.hInstance, szFilePath, 0);
  g_Li.hIconsm = ExtractIconW((HINSTANCE)g_Li.hInstance, szFilePath, 0);

  g_Li.atomClassName = HY_WndRegisterClass(lpszDefaultClassName, NULL, NULL, NULL);

//  g_Li.dwMessage = RegisterWindowMessageW(L"Ex_DirectUI");
//  g_Li.hTableClass = HashTable_Create(47, pfnDefaultFreeData);
//  g_Li.hTableFont = HashTable_Create(17, pfnDefaultFreeFont);
//  g_Li.hTableLayout = HashTable_Create(17, NULL);
//  g_Li.hMemPoolMsg = MemPool_Create(256, sizeof(mempoolmsg_s), 0);
//  g_Li.hHandles = _handle_init();
//  g_Li.dwClickTime = GetDoubleClickTime() * 2;
//
//  g_Li.aryColorsAtom = {ATOM_BACKGROUND_COLOR, ATOM_COLOR_BACKGROUND, ATOM_BORDER_COLOR, ATOM_COLOR_BORDER, ATOM_COLOR,
//                        ATOM_COLOR_NORMAL, ATOM_COLOR_HOVER, ATOM_COLOR_DOWN, ATOM_COLOR_FOCUS, ATOM_COLOR_CHECKED,
//                        ATOM_COLOR_SELECTED, ATOM_COLOR_HOT, ATOM_COLOR_VISTED, ATOM_COLOR_SHADOW};
//  g_Li.aryColorsOffset = {offsetof(obj_s, crBackground_), offsetof(obj_s, crBackground_), offsetof(obj_s, crBorder_),
//                          offsetof(obj_s, crBorder_), offsetof(obj_s, crNormal_), offsetof(obj_s, crNormal_),
//                          offsetof(obj_s, crHover_), offsetof(obj_s, crDown_), offsetof(obj_s, crFocus_),
//                          offsetof(obj_s, crChecked_), offsetof(obj_s, crSelected_), offsetof(obj_s, crHot_),
//                          offsetof(obj_s, crVisted_), offsetof(obj_s, crShadow_)};
//  g_Li.hModuleUser = GetModuleHandleW(L"user32.dll");
//  g_Ri.hRiched20 = LoadLibraryW(L"Msftedit.dll");
//
//  LPVOID i = Ex_MemAlloc(64);
//  INT len;
//  len = LoadStringW(g_Li.hModuleUser, 900, (LPWSTR) i, 64);
//  g_Li.lpStrMin = StrDupW((LPWSTR) i);
//  RtlZeroMemory(i, 64);
//  len = LoadStringW(g_Li.hModuleUser, 901, (LPWSTR) i, 64);
//  g_Li.lpStrMax = StrDupW((LPWSTR) i);
//  RtlZeroMemory(i, 64);
//  len = LoadStringW(g_Li.hModuleUser, 902, (LPWSTR) i, 64);
//  g_Li.lpStrResMin = StrDupW((LPWSTR) i);
//  RtlZeroMemory(i, 64);
//  len = LoadStringW(g_Li.hModuleUser, 903, (LPWSTR) i, 64);
//  g_Li.lpStrResMax = StrDupW((LPWSTR) i);
//  RtlZeroMemory(i, 64);
//  len = LoadStringW(g_Li.hModuleUser, 904, (LPWSTR) i, 64);
//  g_Li.lpStrHelp = StrDupW((LPWSTR) i);
//  RtlZeroMemory(i, 64);
//  len = LoadStringW(g_Li.hModuleUser, 905, (LPWSTR) i, 64);
//  g_Li.lpStrClose = StrDupW((LPWSTR) i);
//  Ex_MemFree(i);
//  INT nError = 0;
//  _canvas_init(&nError);
//  SetProcessDPIAware();
//
//  g_Li.DpiX = 1;
//  g_Li.DpiY = 1;
//  HDC dc = GetDC(NULL);
//  g_Li.DpiX_Real = (FLOAT) GetDeviceCaps(dc, 88) / 96;
//  g_Li.DpiY_Real = (FLOAT) GetDeviceCaps(dc, 90) / 96;
//  ReleaseDC(NULL, dc);
//  if (g_Li.DpiX_Real == 1 && g_Li.DpiY_Real == 1) {
//    Flag_Del(ENGINE_FLAG_DPI_ENABLE);
//  } else {
//    if ((dwGlobalFlags & ENGINE_FLAG_DPI_ENABLE) != 0) {
//      g_Li.DpiX = g_Li.DpiX_Real;
//      g_Li.DpiY = g_Li.DpiY_Real;
//    }
//  }
//  g_Li.lpLogFontDefault = (LOGFONTW *) Ex_MemAlloc(sizeof(LOGFONTW));
//  SystemParametersInfoW(31, sizeof(LOGFONTW), g_Li.lpLogFontDefault, 0);
//  if (!Flag_Query(ENGINE_FLAG_DPI_ENABLE)) {
//    g_Li.lpLogFontDefault->lfHeight = (FLOAT) g_Li.lpLogFontDefault->lfHeight / g_Li.DpiY_Real;
//  }
//
//  _object_init();
//
//  g_Li.aryThemes.clear();
//  Ex_ThemeLoadFromMemory(lpDefaultTheme, dwDefaultThemeLen, 0, 0, TRUE);
//  _layout_init();
//  g_Li.atomSysShadow = Ex_WndRegisterClass(L"SysShadow", 0, 0, 0);
//
//  g_Li.hHookMsgBox = SetWindowsHookExW(WH_CBT, (HOOKPROC) _hook_proc, 0, GetCurrentThreadId());
//
//  g_Li.fContext = new MFFontContext(g_Ri.pDWriteFactory);
//  Ex_SetLastError(nError);
//  return nError == 0;

  return true;
  #else
  #error "Unsupported platform"
  #endif
}

}