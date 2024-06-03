//
// Created by 19254 on 24-6-1.
//
#ifdef _HOST_WINDOWS_
// 抽象实现windows平台的窗口过程

#include <src/gpu/ganesh/gl/GrGLDefines.h>
#include <gpu/GrBackendSurface.h>
#include "HYGUI/Application.h"
#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include "include/core/SkCanvas.h"
#include "include/gpu/gl/GrGLTypes.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"


namespace HYGUI {

LRESULT CALLBACK nWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto windowPtr = GetWindowFromHandle(hWnd);
  switch (message) {
    case WM_PAINT:
      // 绘制窗口
      PrintDebug("WM_PAINT");
      break;
    case WM_CLOSE:
      // 关闭窗口
      HYWindowDestroy(windowPtr);
      break;
    case WM_DESTROY:
      // 销毁窗口
      PostQuitMessage(0);
      break;
    default:
      // 未被捕获的消息
      return CallWindowProcW((WNDPROC) windowPtr->OldProc, hWnd, message, wParam, lParam);
  }
  return 0;
};

HYWindow *GetWindowFromHandle(WINDOWHANDEL handle) {
  for (auto &iter: g_app.WindowsTable) {
    if (iter->Handle == handle) {
      return iter;
    }
  }
  return nullptr;
}

void *HYWindowSkinHook(HYWindow *wnd) {
  //SetLayeredWindowAttributes((HWND) wnd->Handle, RGB(0, 0, 0), 120, LWA_COLORKEY);
  wnd->OldProc = SetWindowLongPtrW((HWND) wnd->Handle, GWLP_WNDPROC, (LONG_PTR) nWndProc);
  wnd->WindowCanvasTarget = GetDC((HWND) wnd->Handle);
  SkImageInfo info = SkImageInfo::MakeN32Premul(wnd->Width, wnd->Height);
  sk_sp<SkSurface> rasterSurface =
    SkSurfaces::Raster(info);

//  GrGLFramebufferInfo fboInfo{ (GrGLuint) 1, GR_GL_RGBA8 };
//  auto bc = GrBackendRenderTargets::MakeGL(wnd->Width, wnd->Height,
//                                           kBottomLeft_GrSurfaceOrigin,
//                                           kBGRA_8888_SkColorType,
//                                           fboInfo);
//  auto bs = SkSurfaces::WrapBackendRenderTarget(
//    (GrRecordingContext *)g_app.GrContext,
//    bc,
//    kBottomLeft_GrSurfaceOrigin,
//    kBGRA_8888_SkColorType,
//    nullptr,
//    nullptr);
  wnd->Surface = rasterSurface.release();
//  auto c = wnd->Surface->getCanvas();
//  c->clear(SK_ColorBLACK);
//  SkPixmap pixmap;
//  if (wnd->Surface->peekPixels(&pixmap)) {
//    BITMAPINFO bmi = {0};
//    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//    bmi.bmiHeader.biWidth = pixmap.width();
//    bmi.bmiHeader.biHeight = -pixmap.height(); // 负值表示顶部到底部扫描
//    bmi.bmiHeader.biPlanes = 1;
//    bmi.bmiHeader.biBitCount = 32;
//    bmi.bmiHeader.biCompression = BI_RGB;
//
//    SetDIBitsToDevice((HDC) wnd->WindowCanvasTarget, 0, 0, pixmap.width(), pixmap.height(),
//                      0, 0, 0, pixmap.height(),
//                      pixmap.addr(), &bmi, DIB_RGB_COLORS);
//  }

//  PrintDebug("e:{}", GetLastError());
//  HDC hCompatibleDC = CreateCompatibleDC((HDC) wnd->WindowCanvasTarget);
//  PrintDebug("e:{}", GetLastError());
//  //填充BLENDFUNCTION结构
//  BLENDFUNCTION blend = {0};
//  blend.BlendOp = AC_SRC_OVER;
//  blend.SourceConstantAlpha = 180;
//  blend.AlphaFormat = AC_SRC_ALPHA;
//  //控制显示位置
//  POINT ptDst = {0, 0};
//  //控制窗口大小
//  SIZE sizeWnd = {wnd->Width, wnd->Height};
//  //为0就行
//  POINT pSrc = {0, 0};
//  //更新分层窗口
//  PrintDebug("e:{}", GetLastError());
//  UpdateLayeredWindow((HWND) wnd->Handle, (HDC) wnd->WindowCanvasTarget, &ptDst, &sizeWnd, hCompatibleDC, &pSrc, NULL,
//                      &blend, ULW_ALPHA);
//  PrintDebug("e:{}", GetLastError());
//  //释放DC
//  DeleteDC((HDC)wnd->WindowCanvasTarget);
//  DeleteDC(hCompatibleDC);


  return nullptr;
}

}


#endif
