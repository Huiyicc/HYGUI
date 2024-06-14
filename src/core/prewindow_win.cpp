//
// Created by 19254 on 24-6-1.
//
#ifdef _HOST_WINDOWS_
// 抽象实现windows平台的窗口过程

#include <src/gpu/ganesh/gl/GrGLDefines.h>
#include <gpu/GrBackendSurface.h>
#include "HYGUI/Application.h"
#include "HYGUI/Window.h"
#include "HYGUI/Mouse.h"
#include "PrivateDefinition.h"
#include "include/core/SkCanvas.h"
#include "include/gpu/gl/GrGLTypes.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"


namespace HYGUI {

void window_paint(HYWindow *windowPtr) {
  //window_recreate_surface(windowPtr);
  auto hWnd = (HWND) windowPtr->Handle;
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
  canvas->clear(static_cast<int>(HYColorRgbToArgb(windowPtr->BackGroundColor, 255)));
  SkPaint paint;
  paint.setAntiAlias(true);
  // 子组件绘制
  canvas->save();
  for (auto obj: windowPtr->Children) {
    HYObjectSendEvent(windowPtr,obj,HYObjectEvent::HYObjectEvent_Paint,0,1);
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
    PrintDebug("Window not found");
    return DefWindowProcW(hWnd, message, wParam, lParam);
  }
  bool obj_event = true;

//  if (message == HYObjectEventTag && lParam == HYObjectEventTag && wParam != NULL) {
//    // 组件消息
//    auto eventInfo = (HYObjectEventInfo *) wParam;
//    if (eventInfo->Event == HYObjectEvent_Paint) {
//      message = WM_PAINT;
//    }
//    obj_event = true;
//  }
  if (message == WM_PAINT) {
    window_paint(windowPtr);
    // obj_event = true;
    if (!windowPtr->IsReady) {
      windowPtr->IsReady = true;
    }
    // obj_event = true;
  } else if (message == WM_CLOSE) {
    // 关闭窗口
    HYWindowDestroy(windowPtr);
    obj_event = false;
  } else if (message == WM_DESTROY) {
    // 销毁窗口
    PostQuitMessage(0);
    obj_event = false;
  } else if (message == WM_SIZE) {
    // 窗口大小改变
    {
      RECT winrect;
      GetWindowRect(hWnd, &winrect);
      windowPtr->Width = winrect.right - winrect.left;
      windowPtr->Height = winrect.bottom - winrect.top;
    }
    window_recreate_surface(windowPtr);
    window_paint(windowPtr);
    obj_event = false;
  } else if (message == WM_MOUSEMOVE) {
    // 鼠标移动
    auto x = GET_X_LPARAM(lParam);
    auto y = GET_Y_LPARAM(lParam);
    // 防止无限触发
    HYPoint np = {x, y};
    if (windowPtr->oldMouseMovePoint == np) {
      return CallWindowProcW((WNDPROC) windowPtr->OldProc, hWnd, message, wParam, lParam);
    }
    windowPtr->oldMouseMovePoint = np;
    if (windowPtr->Drag) {
      // 拖动窗口
      auto mP = HYMouseGetPosition();
      RECT rect;
      GetWindowRect(hWnd, &rect);
      auto dx = mP.x - windowPtr->oldMousePoint.x;
      auto dy = mP.y - windowPtr->oldMousePoint.y;

      MoveWindow(hWnd, windowPtr->oldWinPoint.x + dx, windowPtr->oldWinPoint.y + dy, windowPtr->Width,
                 windowPtr->Height, false);

    } else {

      auto obj = HYObjectObjFromMousePos(windowPtr, x, y);
      if (obj) {
        // 转换坐标
        auto [x1,y1] = HYObjectGetRelativePoint(obj, x, y);
        HYObjectSendEvent(windowPtr, obj, HYObjectEvent_MouseMove, wParam, HYPointGenLParam(x1, y1));
      }
    }
  } else if (message == WM_LBUTTONDOWN) {
    // 鼠标按下
    auto x = GET_X_LPARAM(lParam);
    auto y = GET_Y_LPARAM(lParam);
    if (y < windowPtr->TitleBarHeight) {
      // 标题栏区域内事件
      auto mP = HYMouseGetPosition();
      windowPtr->oldMousePoint = {mP.x, mP.y};
      RECT rect;
      GetWindowRect(hWnd, &rect);
      windowPtr->oldWinPoint = {rect.left, rect.top};
      windowPtr->Drag = true;
    }
  } else if (message == WM_LBUTTONUP) {
    // 鼠标抬起
    windowPtr->Drag = false;
    windowPtr->oldWinPoint = {0, 0};
    windowPtr->oldMousePoint = {0, 0};
  }

//  if (obj_event) {
//    // 组件事件
//    auto eventInfo = (HYObjectEventInfo *) wParam;
//    // HYObjectSendEvent(windowPtr, eventInfo->Object, eventInfo->Event, eventInfo->Param1, eventInfo->Param2);
//    for (auto obj: windowPtr->Children) {
//      for (auto cobj: obj->Children) {
//        if (obj == eventInfo->Object) {
//          // _obj_event(windowPtr, obj, eventInfo->Event, eventInfo->Param1, eventInfo->Param2);
//          HYObjectSendEvent(windowPtr, obj, eventInfo->Event, eventInfo->Param1, eventInfo->Param2);
//          break;
//        }
//      }
//    }
//  }

  return CallWindowProcW((WNDPROC) windowPtr->OldProc, hWnd, message, wParam, lParam);
};

HYWindow *HYWindowGetWindowFromHandle(WINDOWHANDEL handle) {
  if (!g_app.WindowsTable.empty()) {
    for (auto &iter: g_app.WindowsTable) {
      if (iter->Handle == handle) {
        return iter;
      }
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
  LONG_PTR style = GetWindowLongPtrW((HWND) wnd->Handle, GWL_STYLE);
  style &= ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
  SetWindowLongPtrW((HWND) wnd->Handle, GWL_STYLE, style);
  SetWindowPos((HWND) wnd->Handle, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
  window_recreate_surface(wnd);
  window_paint(wnd);
}

uint64_t HYWindowSendEvent(HYWindow *window, uint32_t event, uint64_t param1, uint32_t param2) {
  return SendMessageW((HWND) window->Handle, event, param1, param2);
}

}

#elif defined(_HOST_APPLE_)
namespace HYGUI {
void empty_pre_win() {}
}
#endif
