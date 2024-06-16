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
#include "SDL2/SDL.h"

namespace HYGUI {

ApplicationInfo g_app;


bool HYInit(VOIDPTR ModuleHandle,
            HYGlobalFlag DefaultGlobalFlags,
            CursorPtr DefaultCursor,
            HYString DefaultClassName) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    g_app.LastError = SDL_GetError();
    PrintError(g_app.LastError);
    return false;
  };
  auto &l = g_app;
  g_app.Instance = ModuleHandle;
  g_app.GlobalFlags = DefaultGlobalFlags;
  if (((int) g_app.GlobalFlags & (int) HYGlobalFlag::HYGlobalFlagGraphicNone) ==
      (int) HYGlobalFlag::HYGlobalFlagGraphicNone) {
    g_app.GrContext = GrDirectContexts::MakeGL().release();
  }
  // 注册sdl事件
  g_app.EventCustomStart = SDL_RegisterEvents(2);
  if (g_app.EventCustomStart == (Uint32) -1) {
    g_app.LastError = SDL_GetError();
    PrintError(g_app.LastError);
    return false;
  }
  g_app.EventWindow = g_app.EventCustomStart + 1;
  g_app.EventObject = g_app.EventCustomStart + 2;
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
  SDL_Quit();
  if (g_app.GrContext) {
    SkSafeUnref((GrDirectContext *) g_app.GrContext);
  }
}


}