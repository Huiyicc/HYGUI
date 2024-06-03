//
// Created by 19254 on 24-5-31.
//
#include "HYGUI/Define.h"
#include "HYGUI/Application.h"
#include "PrivateDefinition.h"
#include "HYGUI/Image.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"

namespace HYGUI {

ApplicationInfo g_app;

void HYInit(VOIDPTR ModuleHandle,
            HYGlobalFlag DefaultGlobalFlags,
            CursorPtr DefaultCursor,
            HYString DefaultClassName) {
  g_app.Instance = ModuleHandle;
  g_app.GlobalFlags = DefaultGlobalFlags;
  if (((int) g_app.GlobalFlags & (int) HYGlobalFlag::HYGlobalFlagGraphicGL) ==
      (int) HYGlobalFlag::HYGlobalFlagGraphicGL) {
    // 初始化Skia
    g_app.GrContext = GrDirectContexts::MakeGL().release();
  }
  if (DefaultCursor != nullptr) {
    g_app.Cursor = DefaultCursor;
  } else {
    g_app.Cursor = HYCursorLoadFromDefault();
  }
  if (DefaultClassName.empty()) {
    DefaultClassName = DEFAULT_CLASS_NAME;
  }
  HYWindowRegisterClass(DefaultClassName);
  g_app.DefaultClassName = DefaultClassName;

  // 窗口阴影
  HYWindowRegisterClass(L"SysShadow");
}

void HYExit() {
  if (g_app.GrContext) {
    SkSafeUnref((GrDirectContext*)g_app.GrContext);
  }
}

VOIDPTR HYGetModuleHandle(
  #ifdef _HOST_WINDOWS_
  VOIDPTR lpModuleName
  #else
  #endif
) {
  #ifdef _HOST_WINDOWS_
  return GetModuleHandleW((LPCWSTR) lpModuleName);
  #else
  #error "Unsupported platform"
  #endif
}

}