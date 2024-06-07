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

void window_paint(HYWindow *windowPtr, HWND hWnd) {
  //window_recreate_surface(windowPtr);
  RECT winrect;
  GetWindowRect(hWnd, &winrect);

  //填充BLENDFUNCTION结构
  BLENDFUNCTION blend = {0};
  blend.BlendOp = AC_SRC_OVER;
  blend.SourceConstantAlpha = windowPtr->Diaphaneity;
  blend.AlphaFormat = AC_SRC_ALPHA;
  //控制显示位置
  POINT ptDst = {winrect.left, winrect.top};
  //控制窗口大小
  SIZE sizeWnd = {winrect.right - winrect.left, winrect.bottom - winrect.top};
  POINT pSrc = {0, 0};

  auto canvas = windowPtr->Surface->getCanvas();
  canvas->clear(HYColorRgbToArgb(windowPtr->BackGroundColor, 255));
  SkPaint paint;
  paint.setAntiAlias(true);
  // 子组件绘制
  canvas->save();
  for (auto obj: windowPtr->Children) {
    _obj_paint(obj, canvas, paint, {obj->X, obj->Y, obj->Width, obj->Height});
  }

  SkPixmap pixmap;
  if (windowPtr->Surface->peekPixels(&pixmap)) {
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = pixmap.width();
    bmi.bmiHeader.biHeight = -pixmap.height(); // 负值表示顶部到底部扫描
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    SetDIBitsToDevice((HDC) windowPtr->WindowLayeredCanvas, 0, 0, pixmap.width(), pixmap.height(),
                      0, 0, 0, pixmap.height(),
                      pixmap.addr(), &bmi, DIB_RGB_COLORS);
  }

  //更新分层窗口
  UpdateLayeredWindow(hWnd, (HDC) windowPtr->WindowCanvasTarget, &ptDst, &sizeWnd, (HDC) windowPtr->WindowLayeredCanvas,
                      &pSrc, NULL,
                      &blend, ULW_ALPHA);

};

LRESULT CALLBACK HYWindow_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto windowPtr = HYWindowGetWindowFromHandle(hWnd);
  if (!windowPtr) {
    return DefWindowProcW(hWnd, message, wParam, lParam);
  }
  if (message == 0 && lParam == HYObjectEventTag && wParam != NULL) {
    // 组件消息
    auto eventInfo = (HYObjectEventInfo *) wParam;
    if (eventInfo->Event == HYObjectEvent_Paint) {
      message = WM_PAINT;
    }
  }
  switch (message) {
    case WM_PAINT:
      // 绘制窗口
      window_paint(windowPtr, hWnd);
      break;
    case WM_SIZE: {
      // 窗口大小改变
      {
        RECT winrect;
        GetWindowRect(hWnd, &winrect);
        windowPtr->Width = winrect.right - winrect.left;
        windowPtr->Height = winrect.bottom - winrect.top;
      }
      window_recreate_surface(windowPtr);
      window_paint(windowPtr, hWnd);
    }
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
      return CallWindowProcW((WNDPROC) windowPtr->OldProc, hWnd, message, wParam, lParam);
  }
  return 0;
};

HYWindow *HYWindowGetWindowFromHandle(WINDOWHANDEL handle) {
  for (auto &iter: g_app.WindowsTable) {
    if (iter->Handle == handle) {
      return iter;
    }
  }
  return nullptr;
}

void window_recreate_surface(HYWindow *windowPtr) {
  // 更新HDC/画笔尺寸
  if (windowPtr->Surface) {
    windowPtr->Surface->unref();
  }
  //释放DC
  if (windowPtr->WindowCanvasTarget) {
    DeleteDC((HDC) windowPtr->WindowCanvasTarget);
  }
  if (windowPtr->WindowLayeredCanvas) {
    DeleteDC((HDC) windowPtr->WindowLayeredCanvas);
  }
  if (windowPtr->CustomBmp) {
    DeleteObject((HBITMAP) windowPtr->CustomBmp);
  }

  RECT winrect;
  GetWindowRect((HWND) windowPtr->Handle, &winrect);

  windowPtr->WindowCanvasTarget = GetDC((HWND) windowPtr->Handle);
  windowPtr->WindowLayeredCanvas = CreateCompatibleDC((HDC) windowPtr->WindowCanvasTarget);
  //控制显示位置

  //创建一副与当前DC兼容的位图
  HBITMAP hCustomBmp = CreateCompatibleBitmap((HDC) windowPtr->WindowCanvasTarget, winrect.right - winrect.left,
                                              winrect.bottom - winrect.top);

  //将hCustomBmp指定到hCompatibleDC中

  SelectObject((HDC) windowPtr->WindowLayeredCanvas, hCustomBmp);

  SkImageInfo info = SkImageInfo::MakeN32(windowPtr->Width, windowPtr->Height, kPremul_SkAlphaType);
  auto gpuSurface = SkSurfaces::RenderTarget(
    (GrRecordingContext *) g_app.GrContext,
    skgpu::Budgeted::kNo,
    info
  );
  windowPtr->Surface = gpuSurface.release();
  if (!windowPtr->Surface) {
    // 硬件加速失败
    // PrintDebug("Hardware acceleration failed, fallback to software rendering");
    info = SkImageInfo::MakeN32Premul(windowPtr->Width, windowPtr->Height);
    sk_sp<SkSurface> rasterSurface =
      SkSurfaces::Raster(info);
    windowPtr->Surface = rasterSurface.release();
  }
  windowPtr->Canvas = windowPtr->Surface->getCanvas();
  windowPtr->CustomBmp = hCustomBmp;
}

void HYWindowSkinHook(HYWindow *wnd, HYRGB backGroundColor, int diaphaneity) {
  wnd->EventQueue.SetProcessCallback(processing_object_event);
  wnd->OldProc = SetWindowLongPtrW((HWND) wnd->Handle, GWLP_WNDPROC, (LONG_PTR) HYWindow_WndProc);
  wnd->WindowCanvasTarget = GetDC((HWND) wnd->Handle);
  wnd->BackGroundColor = backGroundColor;
  wnd->Diaphaneity = diaphaneity;
  window_recreate_surface(wnd);
  window_paint(wnd, (HWND) wnd->Handle);
}

void HYWindowSendEvent(HYWindow *window, uint32_t event, intptr_t param1, intptr_t param2) {
  SendMessageW((HWND) window->Handle, event, param1, param2);
}

}


#endif
