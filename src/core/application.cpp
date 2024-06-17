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
#elif defined(_HOST_APPLE_)
#include "include/gpu/gl/GrGLInterface.h"
#include "SDL2/SDL_opengl.h"
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
  #ifdef _HOST_WINDOWS_
  if (((int) g_app.GlobalFlags & (int) HYGlobalFlag::HYGlobalFlagGraphicNone) ==
      (int) HYGlobalFlag::HYGlobalFlagGraphicNone) {
    auto glctx = GrDirectContexts::MakeGL();
    if (glctx) {
      g_app.GrContext = glctx.release();
    }

  }
  #elif defined(_HOST_APPLE_)
  if (((int) g_app.GlobalFlags & (int) HYGlobalFlag::HYGlobalFlagGraphicNone) ==
      (int) HYGlobalFlag::HYGlobalFlagGraphicNone) {
    // 暂时没写硬件加速
    g_app.GrContext = nullptr;
//    sk_sp<const GrGLInterface> interface(GrGLMakeNativeInterface());
//    GrContextOptions options;
//    // options.fSuppressMipmapSupport = true;
//
//    // setup contexts
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);



  }
  #endif
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
  #ifdef _HOST_WINDOWS_
  HYWindowRegisterClass(DefaultClassName);
  g_app.DefaultClassName = DefaultClassName;

  // 窗口阴影
  HYWindowRegisterClass(L"SysShadow");
  #endif
  return true;
}

void HYExit() {
  SDL_Quit();
  if (g_app.GrContext) {
    SkSafeUnref((GrDirectContext *) g_app.GrContext);
  }
}


}