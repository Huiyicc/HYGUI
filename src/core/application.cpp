//
// Created by 19254 on 24-5-31.
//
#define GLFW_INCLUDE_NONE

#include "HYGUI/Define.h"
#include "HYGUI/Application.h"
#include "PrivateDefinition.h"
#include "HYGUI/Image.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
//#include "include/gpu/gl/GrGLInterface.h"

#ifdef _HOST_WINDOWS_

//#include <gl/GL.h>

#endif

//#include <GLFW/glfw3.h>

namespace HYGUI {

ApplicationInfo g_app;

bool HYInit(VOIDPTR ModuleHandle,
            HYGlobalFlag DefaultGlobalFlags,
            CursorPtr DefaultCursor,
            HYString DefaultClassName) {
  g_app.Instance = ModuleHandle;
  g_app.GlobalFlags = DefaultGlobalFlags;
  if (((int) g_app.GlobalFlags & (int) HYGlobalFlag::HYGlobalFlagGraphicNone)==(int) HYGlobalFlag::HYGlobalFlagGraphicNone) {
    g_app.GrContext = GrDirectContexts::MakeGL().release();
  }
//  if (((int) g_app.GlobalFlags & (int) HYGlobalFlag::HYGlobalFlagGraphicGL) ==
//      (int) HYGlobalFlag::HYGlobalFlagGraphicGL) {
////    // 初始化Skia
////    if (glfwInit() != GLFW_TRUE) {
////      g_app.LastError = "glfwInit failed";
////      PrintError(g_app.LastError);
////      return false;
////    }
////    // 创建OpenGL上下文
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
////    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
////    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
////    g_app.GrContext = GrDirectContexts::MakeGL().release();
//  }
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

  return true;
}

void HYExit() {
  if (g_app.GrContext) {
    SkSafeUnref((GrDirectContext *) g_app.GrContext);
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