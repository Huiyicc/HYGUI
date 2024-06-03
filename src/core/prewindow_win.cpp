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
  // 窗口绘制事件
  HDC hLayeredWindowDC = GetDC(hWnd);
  HDC hCompatibleDC = CreateCompatibleDC(hLayeredWindowDC);
  //填充BLENDFUNCTION结构
  BLENDFUNCTION blend = {0};
  blend.BlendOp = AC_SRC_OVER;
  blend.SourceConstantAlpha = 180;
  blend.AlphaFormat = AC_SRC_ALPHA;
  //控制显示位置
  POINT ptDst = {winrect.left, winrect.top};
  //控制窗口大小
  SIZE sizeWnd = {winrect.right - winrect.left, winrect.bottom - winrect.top};
  //为0就行
  POINT pSrc = {0, 0};

  //创建一副与当前DC兼容的位图
  HBITMAP hCustomBmp = NULL;

  hCustomBmp = CreateCompatibleBitmap(hLayeredWindowDC, sizeWnd.cx, sizeWnd.cy);

  //将hCustomBmp指定到hCompatibleDC中
  //PrintDebug("e:{}", GetLastError());
  SelectObject(hCompatibleDC, hCustomBmp);
  //PrintDebug("e:{}", GetLastError());
  auto c = windowPtr->Surface->getCanvas();
  c->clear(SK_ColorBLACK);
  SkPixmap pixmap;
  if (windowPtr->Surface->peekPixels(&pixmap)) {
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = pixmap.width();
    bmi.bmiHeader.biHeight = -pixmap.height(); // 负值表示顶部到底部扫描
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    SetDIBitsToDevice(hCompatibleDC, 0, 0, pixmap.width(), pixmap.height(),
                      0, 0, 0, pixmap.height(),
                      pixmap.addr(), &bmi, DIB_RGB_COLORS);
  }
  PrintDebug("sizeWnd.cx:{},sizeWnd.cy:{}", sizeWnd.cx, sizeWnd.cy);
  PrintDebug("pixmap.width:{},pixmap.height:{}", pixmap.width(), pixmap.height());


  //更新分层窗口
  UpdateLayeredWindow(hWnd, hLayeredWindowDC, &ptDst, &sizeWnd, hCompatibleDC, &pSrc, NULL,
                      &blend, ULW_ALPHA);

  //释放DC
  DeleteDC(hLayeredWindowDC);
  DeleteDC(hCompatibleDC);


};

LRESULT CALLBACK HYWindow_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto windowPtr = HYWindowGetWindowFromHandle(hWnd);
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
  if (windowPtr->Surface) {
    windowPtr->Surface->unref();
  }
  SkImageInfo info = SkImageInfo::MakeN32Premul(windowPtr->Width, windowPtr->Height);
  sk_sp<SkSurface> rasterSurface =
    SkSurfaces::Raster(info);
  windowPtr->Surface = rasterSurface.release();
}

void *HYWindowSkinHook(HYWindow *wnd) {
  wnd->OldProc = SetWindowLongPtrW((HWND) wnd->Handle, GWLP_WNDPROC, (LONG_PTR) HYWindow_WndProc);
  wnd->WindowCanvasTarget = GetDC((HWND) wnd->Handle);
  window_recreate_surface(wnd);
  window_paint(wnd, (HWND) wnd->Handle);
  return nullptr;
}

}


#endif
