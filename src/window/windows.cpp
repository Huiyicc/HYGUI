//
// Created by 19254 on 24-5-13.
//

#include <HYGUI/core/window.h>
#include "HYGUI/utils/help.h"

#ifdef _HOST_WINDOWS_
#include <windows.h>
#endif


namespace HYGUI {

WINDOWHAND HCreateWindow(WINDOWHAND parent,
                         float left, float top,
                         float width, float height,
                         const HString& title,
                         bool isResizable,
                         uint32_t style,
                         bool taskbar) {

  HRECT rc = {0};
  GetWorkingAreaRECT(&rc);
  if (top == WINDOWPOS_USEDEFAULE) {
    top = rc.Top + (rc.Bottom - rc.Top - height) / 2;
  }
  if (left == WINDOWPOS_USEDEFAULE) {
    left = rc.Left + (rc.Right - rc.Left - width) / 2;
  }
  if (isResizable) {
    style = static_cast<WINDOWSTYLE>( style | WINDOWSTYLE::WINDOWSTYLE_SIZEBOX);
  }
  uint32_t styleEx = 0;
  if (parent == nullptr) {
    styleEx = taskbar ? WINDOWSTYLEEX_APPWINDOW : WINDOWSTYLEEX_TOOLWINDOW;
  } else {
    if (taskbar)
      styleEx = WINDOWSTYLEEX_APPWINDOW;
  }
  #ifdef _HOST_WINDOWS_
  static HINSTANCE__ *hMod = nullptr;
  if (hMod == nullptr) {
    hMod = GetModuleHandle(nullptr);
  }
  auto hWnd = CreateWindowExW(styleEx, WINDOWCLASSNAME,
                              title.toWString().c_str(), style,
                              static_cast<int>(left), static_cast<int>(top), static_cast<int>(width),
                              static_cast<int>(height),
                              static_cast<HWND>(parent), nullptr, hMod, nullptr);
  return hWnd;
  #else
  #error "Not implemented"
  #endif

  return nullptr;
};

bool HRegisterWindowClass(HString className) {
  #ifdef _HOST_WINDOWS_
  auto defultCallback =
    [](HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
      return DefWindowProcW(hWnd, Msg, wParam, lParam);
    };
  WNDCLASSW wc = {0};
  wc.lpfnWndProc = defultCallback;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.lpszClassName = className.toWString().empty() ? WINDOWCLASSNAME : className.toWString().c_str();
  wc.style = 8;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) (16);
  if (RegisterClassW(&wc) == 0) {
    return false;
  }
  return true;
  #else
  #error "Not implemented"
  #endif
  return false;
};

uint32_t HWindowMessageLoop(WINDOWHAND hWnd) {
  #ifdef _HOST_WINDOWS_
  MSG msg;
  while (IsWindow(static_cast<HWND>(hWnd))) {
    while (GetMessage(&msg, static_cast<HWND>(hWnd), 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return msg.wParam;
  #else
  #error "Not implemented"
  #endif
  return 0;
};

uint32_t HWindowMessageLoopDialog(WINDOWHAND parent, WINDOWHAND hWnd) {
  #ifdef _HOST_WINDOWS_
  if (parent != nullptr) {
    // duang↑duang↓duang↑duang↓
    SendMessageW(static_cast<HWND>(parent), WM_MOUSELEAVE, 0, 0);
  }
  MSG msg;
  while (IsWindow(static_cast<HWND>(hWnd))) {
    while (GetMessage(&msg, static_cast<HWND>(hWnd), 0, 0)) {
      if (msg.hwnd != static_cast<HWND>(hWnd)) {
        if (msg.message > 254 && msg.message < 264 || msg.message > 511 && msg.message < 526) {
          if (msg.message == 513 || msg.message == 515 || msg.message == 516 || msg.message == 518 ||
              msg.message == 519 || msg.message == 521 || msg.message == 523 || msg.message == 525) {
            // duang↑duang↓duang↑duang↓
            SendMessageW(static_cast<HWND>(hWnd), WM_SYSCHAR, 0, 0);
            SetForegroundWindow(static_cast<HWND>(hWnd));
          }
          continue;
        }
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return msg.wParam;
  #else
  #error "Not implemented"
  #endif
  return 0;
};


}


