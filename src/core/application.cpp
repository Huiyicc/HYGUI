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
            HYGlobalFlag DefaultGlobalFlags) {
  HYString DefaultClassName = DEFAULT_CLASS_NAME;
  // 初始化sdl gl
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  #if defined(_HOST_APPLE_)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  #endif
  #if defined(_HOST_ANDROID_) || defined(_HOST_IOS_)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                  SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP |
                  SDL_WINDOW_ALLOW_HIGHDPI;
  #else
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  #endif
  //SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

  g_app.kStencilBits = 8;  // skia需要8位模板缓冲区
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, g_app.kStencilBits);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    g_app.LastError = SDL_GetError();
    PrintError(g_app.LastError);
    return false;
  };
  g_app.Instance = ModuleHandle;
  g_app.GlobalFlags = DefaultGlobalFlags;

  // 注册sdl事件
  g_app.EventCustomStart = SDL_RegisterEvents(2);
  if (g_app.EventCustomStart == (Uint32) -1) {
    g_app.LastError = SDL_GetError();
    PrintError(g_app.LastError);
    return false;
  }
  g_app.EventWindow = g_app.EventCustomStart + 1;
  g_app.EventObject = g_app.EventCustomStart + 2;
//  if (DefaultCursor != nullptr) {
//    g_app.Cursor = DefaultCursor;
//  } else {
//    // g_app.Cursor = HYCursorLoadFromDefault();
//    g_app.Cursor = nullptr;
//  }
  g_app.Cursor = nullptr;
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