//
// Created by 19254 on 24-5-31.
//

#include "HYGUI/Window.h"
#include "PrivateDefinition.h"


namespace HYGUI {


bool HYWindowRegisterClass(const HYString &className, const HYString &iconPath, const HYString &cursorPath) {
#ifdef _HOST_WINDOWS_
  WNDCLASSEXW WndClass = {0};
  WndClass.cbSize = sizeof(WNDCLASSEXW);
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  WndClass.lpfnWndProc = DefWindowProc;
  WndClass.hInstance = (HINSTANCE) g_app.Instance;
  if (cursorPath.empty()) {
    WndClass.hCursor = g_app.Cursor ? (HCURSOR) g_app.Cursor : LoadCursorW(nullptr,
                                                                           reinterpret_cast<LPCWSTR>(IDC_ARROW));
  } else {
    WndClass.hCursor = LoadCursorFromFileW(cursorPath.toWStringView().data());
  }
  WndClass.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH);
  if (iconPath.empty()) {
    WndClass.hIcon = g_app.Icon ? (HICON) g_app.Icon : LoadIconW(nullptr, reinterpret_cast<LPCWSTR>(IDI_APPLICATION));
    WndClass.hIconSm = g_app.IconSm ? (HICON) g_app.IconSm : LoadIconW(nullptr,
                                                                       reinterpret_cast<LPCWSTR>(IDI_APPLICATION));
  } else {
    WndClass.hIcon = LoadIconW((HINSTANCE) g_app.Instance, iconPath.toWStringView().data());
    WndClass.hIconSm = LoadIconW((HINSTANCE) g_app.Instance, iconPath.toWStringView().data());
  }
  WndClass.lpszClassName = className.toWStringView().data();
  return RegisterClassExW(&WndClass);
#else
#error "Unsupported platform"
#endif
}

HYWindow *HYWindowCreate(HYWindow *parent, const HYString &title, int x, int y, int width, int height) {
#ifdef _HOST_WINDOWS_
  if (x == WINDOWCREATEPOINT_USEDEFAULT) {
    x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
  }
  if (y == WINDOWCREATEPOINT_USEDEFAULT) {
    y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
  }
  HWND hWnd = CreateWindowExW(WS_EX_LAYERED, g_app.DefaultClassName.toWStringView().data(),
                              title.toWStringView().data(),
                              (WS_OVERLAPPEDWINDOW | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_LAYERED) & ~WS_SYSMENU,
                              x, y, width,
                              height, parent ? (HWND) parent->Handle : nullptr,
                              nullptr, (HINSTANCE) g_app.Instance, nullptr);
  if (hWnd == nullptr) {
    return nullptr;
  }
  auto window = new HYWindow;
  window->Handle = hWnd;
  RECT wrect;
  GetWindowRect(hWnd, &wrect);
  window->Width = wrect.right - wrect.left;
  window->Height = wrect.bottom - wrect.top;
  window->X = x;
  window->Y = y;

  if (g_app.WindowsTable.find(window) != g_app.WindowsTable.end()) {
    // ????什么玩意
    delete window;
    return nullptr;
  }
  g_app.WindowsTable.insert(window);

  return window;
#else
# 实现创建窗口
#error "Unsupported platform"
#endif
}

void HYWindowDestroy(HYWindow *wnd) {
  if (wnd->Handle) {
    #ifdef _HOST_WINDOWS_
    DestroyWindow(static_cast<HWND>(wnd->Handle));
    #else
    #error "Unsupported platform"
    #endif
    // 清理资源
    if (wnd->Surface) {
      wnd->Surface->unref();
    }
    //释放DC
    if (wnd->WindowCanvasTarget) {
      DeleteDC((HDC) wnd->WindowCanvasTarget);
    }
    if (wnd->WindowLayeredCanvas) {
      DeleteDC((HDC) wnd->WindowLayeredCanvas);
    }
    if (wnd->CustomBmp) {
      DeleteObject((HBITMAP) wnd->CustomBmp);
    }
    delete wnd;
    g_app.WindowsTable.erase(wnd);

  }

}

bool HYWindowShow(HYWindow *wnd) {
#ifdef _HOST_WINDOWS_
  return ShowWindow(static_cast<HWND>(wnd->Handle), SW_SHOW)
         && UpdateWindow(static_cast<HWND>(wnd->Handle));
#else
#error "Unsupported platform"
#endif
}

uint32_t HYWindowMessageLoop(HYWindow *wnd) {
#ifdef _HOST_WINDOWS_
  MSG msg;
  while (IsWindow(static_cast<HWND>(wnd->Handle))) {
    if (!GetMessageW(&msg, static_cast<HWND>(wnd->Handle), 0, 0)) {
      break;
    }
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
  return msg.wParam;
#else
#error "Unsupported platform"
#endif

}


uint32_t HYWindowMessageLoopDialog(HYWindow *wnd, HYWindow *parent) {
#ifdef _HOST_WINDOWS_
  if (parent != nullptr) {
    // duang↑duang↓duang↑duang↓
    SendMessageW(static_cast<HWND>(parent->Handle), WM_MOUSELEAVE, 0, 0);
  }
  MSG msg;
  while (IsWindow(static_cast<HWND>(wnd->Handle))) {
    if (!GetMessageW(&msg, static_cast<HWND>(wnd->Handle), 0, 0)) {
      break;
    }
    if (msg.hwnd != static_cast<HWND>(wnd->Handle)) {
      if (msg.message > 254 && msg.message < 264 || msg.message > 511 && msg.message < 526) {
        if (msg.message == 513 || msg.message == 515 || msg.message == 516 || msg.message == 518 ||
            msg.message == 519 || msg.message == 521 || msg.message == 523 || msg.message == 525) {
          // duang↑duang↓duang↑duang↓
          SendMessageW(static_cast<HWND>(wnd->Handle), WM_SYSCHAR, 0, 0);
          SetForegroundWindow(static_cast<HWND>(wnd->Handle));
        }
        continue;
      }
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
#else
#error "Unsupported platform"
#endif

}


}

