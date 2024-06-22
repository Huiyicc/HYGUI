//
// Created by huiyi on 24-6-22.
//
#ifdef _HOST_LINUX_

#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include "SDL2/SDL.h"
#include "include/core/SkCanvas.h"
#include "include/gpu/gl/GrGLTypes.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_opengl.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <src/gpu/ganesh/gl/GrGLDefines.h>

namespace HYGUI {

void HYWindowSkinHook(HYWindow *wnd, HYRGB backGroundColor, int diaphaneity) {
  wnd->EventQueue.SetProcessCallback(processing_object_event);
  wnd->BackGroundColor = HYColorRGBToInt(backGroundColor);
  wnd->Diaphaneity = diaphaneity;
  SDL_SetWindowOpacity(wnd->SDLWindow,(float)(diaphaneity) / 255.0f);

  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  if (SDL_GetWindowWMInfo(wnd->SDLWindow, &wmInfo)) {
    SDL_SetWindowBordered(wnd->SDLWindow, SDL_FALSE);
  }

  window_recreate_surface(wnd);

  SDL_Event event;
  event.type = g_app.EventWindow;
  event.window.windowID = wnd->ID;
  event.window.event = HYWindowEvent_Paint;
  event.window.data1 = 0;
  event.window.data2 = 0;
  SDL_PushEvent(&event);
}

void window_recreate_surface(HYWindow *windowPtr) {
  // 更新HDC/画笔尺寸
  if (windowPtr->Surface) {
    windowPtr->Surface->unref();
  }

  // windowPtr->WindowCanvasTarget = GetDC((HWND) windowPtr->Handle);
  SDL_SysWMinfo winfo;
  SDL_GetWindowWMInfo(windowPtr->SDLWindow, &winfo);
  // windowPtr->WindowCanvasTarget = winfo.info.x11.display;

  // 将附加到屏幕上的帧缓冲对象包装在Skia渲染目标中，以便Skia可以对其进行渲染
  GrGLint buffer;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
  GrGLFramebufferInfo binfo;
  binfo.fFBOID = (GrGLuint) buffer;
  #if defined(_HOST_ANDROID_)
  binfo.fFormat =  GL_RGB8_OES;
  #else
  binfo.fFormat = GL_RGB8;
  #endif
  // GrBackendRenderTarget target(dw, dh, kMsaaSampleCount, kStencilBits, info);
  auto grtarget = GrBackendRenderTargets::MakeGL(windowPtr->ClientRect.width, windowPtr->ClientRect.height,
                                                 0, g_app.kStencilBits,
                                                 binfo);

  SkSurfaceProps props;
  sk_sp<SkSurface> surface(SkSurfaces::WrapBackendRenderTarget(((GrDirectContext *) windowPtr->GrCtx), grtarget,
                                                               kBottomLeft_GrSurfaceOrigin,
                                                               kRGB_888x_SkColorType, nullptr, &props));
  windowPtr->Surface = surface.release();
  if (!windowPtr->Surface) {
    // 硬件加速失败
    PrintError("Hardware acceleration failed, fallback to software rendering");
    exit(1);
  }
  windowPtr->Canvas = windowPtr->Surface->getCanvas();
  // windowPtr->CustomBmp = hCustomBmp;
}

void adjustwindow_by_sdl(uint32_t id, SDL_Window *sdl_window, void *handel) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto hWnd = (Display *) handel;
  for (auto window: g_app.WindowsTable) {
    if (window->ID != id) {
      continue;
    }
    if (window->Handle == hWnd) {
      break;
    }
    SDL_SysWMinfo winfo;
    SDL_GetWindowWMInfo(sdl_window, &winfo);
    window->Handle = hWnd;
    window->SDLWindow = sdl_window;
    SDL_GetWindowPosition(sdl_window, &window->X, &window->Y);
    SDL_GetWindowSize(sdl_window, &window->Width, &window->Height);
    window->ClientRect = {0, 0, window->Width, window->Height};
    // window->WindowCanvasTarget = winfo.info.cocoa.window;
    break;
  }
}

void HYWindowDestroy(HYWindowHandel wnd) {
  if (!wnd->Handle) { return; }
  SDL_DestroyWindow(wnd->SDLWindow);

  // 清理资源
  if (wnd->Surface) {
    wnd->Surface->unref();
  }
//  //释放DC
//  if (wnd->WindowCanvasTarget) {
//    DeleteDC((HDC)
//                 wnd->WindowCanvasTarget);
//  }
//  if (wnd->WindowLayeredCanvas) {
//    DeleteDC((HDC)
//                 wnd->WindowLayeredCanvas);
//  }
//  if (wnd->CustomBmp) {
//    DeleteObject((HBITMAP) wnd->CustomBmp);
//  }
  delete wnd;
  g_app.WindowsTable.erase(wnd);

}

}

#endif
