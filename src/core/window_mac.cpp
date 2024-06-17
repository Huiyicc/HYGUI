//
// Created by 回忆 on 24-6-17.
//

#ifdef _HOST_APPLE_

#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include "SDL2/SDL.h"
#include "include/core/SkCanvas.h"
#include "include/gpu/gl/GrGLTypes.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include <SDL2/SDL_syswm.h>


namespace HYGUI {

void HYWindowSkinHook(HYWindow *wnd, HYRGB backGroundColor, int diaphaneity) {
  wnd->EventQueue.SetProcessCallback(processing_object_event);
  //wnd->OldProc = SetWindowLongPtrW((HWND) wnd->Handle, GWLP_WNDPROC, (LONG_PTR) HYWindow_WndProc);
  // wnd->WindowCanvasTarget = GetDC((HWND) wnd->Handle);
  wnd->BackGroundColor = HYColorRGBToInt(backGroundColor);
  wnd->Diaphaneity = diaphaneity;
//  LONG_PTR style = GetWindowLongPtrW((HWND) wnd->Handle, GWL_STYLE);
//  style &= ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
//  SetWindowLongPtrW((HWND) wnd->Handle, GWL_STYLE, style);
//  SetWindowPos((HWND) wnd->Handle, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

  SDL_SetWindowOpacity(wnd->SDLWindow,(float)(diaphaneity) / 255.0f);
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

//  RECT winrect;
//  GetWindowRect((HWND) windowPtr->Handle, &winrect);

  // windowPtr->WindowCanvasTarget = GetDC((HWND) windowPtr->Handle);
  SDL_SysWMinfo winfo;
  SDL_GetWindowWMInfo(windowPtr->SDLWindow, &winfo);
  windowPtr->WindowCanvasTarget = winfo.info.cocoa.window;
  // windowPtr->WindowLayeredCanvas = CreateCompatibleDC((HDC) windowPtr->WindowCanvasTarget);
  //控制显示位置

  //创建一副与当前DC兼容的位图
//  HBITMAP hCustomBmp = CreateCompatibleBitmap((HDC) windowPtr->WindowCanvasTarget, winrect.right - winrect.left,
//                                              winrect.bottom - winrect.top);

  //将hCustomBmp指定到hCompatibleDC中
  // SelectObject((HDC) windowPtr->WindowLayeredCanvas, hCustomBmp);
  auto colorSpace = SkColorSpace::MakeSRGB();
  SkImageInfo info = SkImageInfo::MakeN32(windowPtr->Width, windowPtr->Height,SkAlphaType::kPremul_SkAlphaType);
//  auto gpuSurface = SkSurfaces::RenderTarget(
//      (GrRecordingContext *) g_app.GrContext,
//      skgpu::Budgeted::kNo,
//      info
//  );
//  windowPtr->Surface = gpuSurface.release();
  windowPtr->Surface=nullptr;
  if (!windowPtr->Surface) {
    // 硬件加速失败
    // PrintDebug("Hardware acceleration failed, fallback to software rendering");
    sk_sp<SkSurface> rasterSurface =
        SkSurfaces::Raster(info);
    windowPtr->Surface = rasterSurface.release();
  }
  windowPtr->Canvas = windowPtr->Surface->getCanvas();
  // windowPtr->CustomBmp = hCustomBmp;
}

void adjustwindow_by_sdl(uint32_t id, SDL_Window *sdl_window, void *handel) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto hWnd = (NSWindow *) handel;
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
    window->WindowCanvasTarget = winfo.info.cocoa.window;
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