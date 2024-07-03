//
// Created by 19254 on 24-5-31.
//
#ifdef _HOST_WINDOWS_


#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include "SDL2/SDL.h"
#include "include/core/SkCanvas.h"
#include "include/gpu/gl/GrGLTypes.h"
// #include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>
#include <dwmapi.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <src/gpu/ganesh/gl/GrGLDefines.h>

namespace HYGUI {

void window_hook_handel(HYWindow *windowPtr) {
  if (!windowPtr->Handle) return;
  //window_make_window_transparent(windowPtr, RGB(255, 0, 255));
}

bool window_make_window_transparent(HYWindowHandel window, COLORREF colorKey) {
  auto hWnd = (HWND) window->Handle;
  SetWindowLongPtrA(hWnd, GWL_EXSTYLE, GetWindowLongPtrA(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
  // Set transparency color
  return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}

void window_recreate_surface(HYWindowHandel windowPtr) {
  // 更新HDC/画笔尺寸
  if (windowPtr->Surface) {
    HYResourceRemove(ResourceType::ResourceType_Other, windowPtr->Surface);
  }

  SDL_GL_MakeCurrent(windowPtr->SDLWindow, windowPtr->SDLOpenGl);

  RECT winrect;
  GetWindowRect((HWND) windowPtr->Handle, &winrect);

  SDL_SysWMinfo winfo;
  SDL_GetWindowWMInfo(windowPtr->SDLWindow, &winfo);

  // 将附加到屏幕上的帧缓冲对象包装在Skia渲染目标中，以便Skia可以对其进行渲染
  GrGLint buffer;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
  GrGLFramebufferInfo binfo;
  binfo.fFBOID = (GrGLuint) buffer;
#if defined(_HOST_ANDROID_)
  binfo.fFormat = GL_RGBA8_OES;
#else
  binfo.fFormat = GL_RGBA8;
#endif
  SDL_GL_GetDrawableSize(windowPtr->SDLWindow, &windowPtr->ClientRect.width, &windowPtr->ClientRect.height);
  // GrBackendRenderTarget target(dw, dh, kMsaaSampleCount, kStencilBits, info);
  auto grtarget = GrBackendRenderTargets::MakeGL(windowPtr->ClientRect.width, windowPtr->ClientRect.height,
                                                 0, 8,
                                                 binfo);

  SkSurfaceProps props = {0, kUnknown_SkPixelGeometry};
  ;
  sk_sp<SkSurface> surface(SkSurfaces::WrapBackendRenderTarget(((GrDirectContext *) windowPtr->GrCtx), grtarget,
                                                               kBottomLeft_GrSurfaceOrigin,
                                                               kRGBA_8888_SkColorType, nullptr, &props));
  windowPtr->Surface = surface.release();
  if (!windowPtr->Surface) {
    // 硬件加速失败
    PrintError("Hardware acceleration failed, fallback to software rendering");
    exit(1);
  }
  HYResourceRegisterOther(windowPtr->Surface, "skia surface", [](void *ptr) {
    SkSafeUnref((SkSurface *) ptr);
  });
  windowPtr->Canvas = windowPtr->Surface->getCanvas();

  HYWindowSendEventRePaint(windowPtr);
}

void adjustwindow_by_sdl(HYWindowHandel window, void *newhandel) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  HWND hWnd = (HWND) newhandel;
  SDL_SysWMinfo winfo;
  SDL_GetWindowWMInfo(window->SDLWindow, &winfo);
  window->Handle = hWnd;
  SDL_GetWindowPosition(window->SDLWindow, &window->X, &window->Y);
  SDL_GetWindowSize(window->SDLWindow, &window->Width, &window->Height);
  window->ClientRect = {0, 0, window->Width, window->Height};
  window_hook_handel(window);
  //  HWND hWnd = (HWND) handel;
  //  for (auto window: g_app.WindowsTable) {
  //    if (window->ID != id) {
  //      continue;
  //    }
  //    if (window->Handle == hWnd) {
  //      break;
  //    }
  //    PrintDebug("Adjust window {} wnd:{} new:{}", id, (uint64_t)window->Handle,(uint64_t )handel);
  //    SDL_SysWMinfo winfo;
  //    SDL_GetWindowWMInfo(sdl_window, &winfo);
  //    window->Handle = hWnd;
  //    window->SDLWindow = sdl_window;
  //    SDL_GetWindowPosition(sdl_window, &window->X, &window->Y);
  //    SDL_GetWindowSize(sdl_window, &window->Width, &window->Height);
  //    window->ClientRect = {0, 0, window->Width, window->Height};
  //    window_hook_handel(window);
  //    break;
  //  }
}

}// namespace HYGUI
#else
void _WINDW_WIN() {
  return;
}
#endif