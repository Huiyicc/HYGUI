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
  //wnd->OldProc = SetWindowLongPtrW((HWND) wnd->Handle, GWLP_WNDPROC, (LONG_PTR) HYWindow_WndProc);
  wnd->WindowCanvasTarget = GetDC((HWND) wnd->Handle);
  wnd->BackGroundColor = HYColorRGBToInt(backGroundColor);
  wnd->Diaphaneity = diaphaneity;
  LONG_PTR style = GetWindowLongPtrW((HWND) wnd->Handle, GWL_STYLE);
  style &= ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
  SetWindowLongPtrW((HWND) wnd->Handle, GWL_STYLE, style);
  SetWindowPos((HWND) wnd->Handle, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

  SDL_SetWindowOpacity(wnd->SDLWindow, (float) (diaphaneity) / 255.0f);
  window_recreate_surface(wnd);
  // window_paint(wnd);
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
  //释放DC
//  if (windowPtr->WindowCanvasTarget) {
//    DeleteDC((HDC) windowPtr->WindowCanvasTarget);
//  }
//  if (windowPtr->WindowLayeredCanvas) {
//    DeleteDC((HDC) windowPtr->WindowLayeredCanvas);
//  }
//  if (windowPtr->CustomBmp) {
//    DeleteObject((HBITMAP) windowPtr->CustomBmp);
//  }

  RECT winrect;
  GetWindowRect((HWND) windowPtr->Handle, &winrect);

  // windowPtr->WindowCanvasTarget = GetDC((HWND) windowPtr->Handle);
  SDL_SysWMinfo winfo;
  SDL_GetWindowWMInfo(windowPtr->SDLWindow, &winfo);
  windowPtr->WindowCanvasTarget = winfo.info.win.hdc;

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
  // 高dpi
//  SDL_DisplayMode dm;
//  SDL_GetDesktopDisplayMode(0, &dm);
//  windowPtr->Canvas->scale((float) (windowPtr->ClientRect.width) / (float) dm.w,
//                           (float) windowPtr->ClientRect.height / (float) dm.h);

  //  SkColorType colorType = kRGBA_8888_SkColorType;
//  GrGLint buffer;
//  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
//  auto bg = GrBackendRenderTargets::MakeGL(windowPtr->Width, windowPtr->Height, 0, 0, GrGLFramebufferInfo{(GrGLuint)buffer, GL_BGRA8_EXT});
//  sk_sp<SkSurface> surface = SkSurfaces::WrapBackendRenderTarget(
//    ((GrDirectContext *)windowPtr->GrCtx), bg, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr);
//  windowPtr->Surface = surface.release();
//  backendRenderTarget(windowPtr->Width, windowPtr->Height, 0, 0, GrGLFramebufferInfo{(GrGLuint)buffer, GL_RGBA8});


//  SkSurfaceProps surfaceProps(0, kUnknown_SkPixelGeometry);
//  GrGLFramebufferInfo framebufferInfo;
//  framebufferInfo.fFBOID = 0; // 默认帧缓冲ID
//  framebufferInfo.fFormat = GR_GL_RGBA8;
//  SkColorType colorType = kRGBA_8888_SkColorType;
//  auto bgr = GrBackendRenderTargets::MakeGL(windowPtr->Width, windowPtr->Height, 0, 8, framebufferInfo);
//  sk_sp<SkSurface> surface(SkSurfaces::WrapBackendRenderTarget(
//    ((GrDirectContext *)windowPtr->GrCtx),
//    bgr,
//    kBottomLeft_GrSurfaceOrigin,
//    colorType,
//    nullptr,
//    &surfaceProps)
//    );
//  windowPtr->Surface = surface.release();
//  windowPtr->Canvas = windowPtr->Surface->getCanvas();

//  SkImageInfo info = SkImageInfo::MakeN32(windowPtr->Width, windowPtr->Height,SkAlphaType::kPremul_SkAlphaType);
//  auto gpuSurface = SkSurfaces::RenderTarget(
//    (GrDirectContext *) windowPtr->GrCtx,
//    skgpu::Budgeted::kNo,
//    info
//  );
//  windowPtr->Surface = gpuSurface.release();
//  if (!windowPtr->Surface) {
//    // 硬件加速失败
//    PrintError("Hardware acceleration failed, fallback to software rendering");
//    exit(1);
//  }
//  windowPtr->Canvas = windowPtr->Surface->getCanvas();


////  SkImageInfo imageInfo = SkImageInfo::MakeN32Premul(winrect.right - winrect.left,
////                                                     winrect.bottom - winrect.top);
//  SkImageInfo info = SkImageInfo::MakeN32(windowPtr->Width, windowPtr->Height,SkAlphaType::kPremul_SkAlphaType);
//  auto surface = SkSurfaces::RenderTarget(((GrDirectContext*)windowPtr->GrCtx),
//                                          skgpu::Budgeted::kNo,
//                                          info);
//  windowPtr->Surface = surface.release();
//  windowPtr->Canvas = windowPtr->Surface->getCanvas();



//  windowPtr->WindowLayeredCanvas = CreateCompatibleDC((HDC) windowPtr->WindowCanvasTarget);
//  //控制显示位置
//
//  //创建一副与当前DC兼容的位图
//  HBITMAP hCustomBmp = CreateCompatibleBitmap((HDC) windowPtr->WindowCanvasTarget, winrect.right - winrect.left,
//                                              winrect.bottom - winrect.top);
//
//  //将hCustomBmp指定到hCompatibleDC中
//  SelectObject((HDC) windowPtr->WindowLayeredCanvas, hCustomBmp);
//  auto colorSpace = SkColorSpace::MakeSRGB();
//  SkImageInfo info = SkImageInfo::MakeN32(windowPtr->Width, windowPtr->Height,SkAlphaType::kPremul_SkAlphaType);
//  auto gpuSurface = SkSurfaces::RenderTarget(
//    (GrRecordingContext *) g_app.GrContext,
//    skgpu::Budgeted::kNo,
//    info
//  );
//  windowPtr->Surface = gpuSurface.release();
//  if (!windowPtr->Surface) {
//    // 硬件加速失败
//    // PrintDebug("Hardware acceleration failed, fallback to software rendering");
//    sk_sp<SkSurface> rasterSurface =
//      SkSurfaces::Raster(info);
//    windowPtr->Surface = rasterSurface.release();
//  }
//  windowPtr->Canvas = windowPtr->Surface->getCanvas();
//  windowPtr->CustomBmp = hCustomBmp;
}

void adjustwindow_by_sdl(uint32_t id, SDL_Window *sdl_window, void *handel) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  HWND hWnd = (HWND) handel;
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
    window->WindowCanvasTarget = winfo.info.win.hdc;
    break;
  }
}

void HYWindowDestroy(HYWindowHandel wnd) {
  if (!wnd->Handle) { return; }
  if (wnd->GrCtx) {
    ((GrDirectContext *) wnd->GrCtx)->unref();
  }
  SDL_DestroyWindow(wnd->SDLWindow);
  SDL_GL_DeleteContext((SDL_GLContext *) wnd->SDLGl);

  // 清理资源
  if (wnd->Surface) {
    wnd->Surface->unref();
  }
  //释放DC
  if (wnd->WindowCanvasTarget) {
    DeleteDC((HDC)
               wnd->WindowCanvasTarget);
  }
  if (wnd->WindowLayeredCanvas) {
    DeleteDC((HDC)
               wnd->WindowLayeredCanvas);
  }
  if (wnd->CustomBmp) {
    DeleteObject((HBITMAP) wnd->CustomBmp);
  }
  delete wnd;
  g_app.WindowsTable.erase(wnd);

}

}
#else
void _WINDW_WIN() {
    return;
}
#endif