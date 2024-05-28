//
// Created by 19254 on 24-5-28.
//
#include <PrivateDefinition.h>
#include <cstdint>

namespace HYGUI {

intptr_t HY_WndRegisterClass(const wchar_t *lpwzClassName,
                             intptr_t hIcon,
                             intptr_t hIconsm,
                             intptr_t hCursor) {
  #ifdef _HOST_WINDOWS_
  WNDCLASSEX wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  wc.lpfnWndProc = DefWindowProcW;
  wc.hInstance = (HINSTANCE) g_Li.hInstance;
  wc.hCursor = hCursor == NULL ? (HCURSOR) g_Li.hCursor : (HCURSOR) hCursor;
  wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); //NULL_BRUSH
  wc.hIcon = hIcon == NULL ? (HICON) g_Li.hIcon : (HICON) hIcon;
  wc.hIconSm = hIconsm == NULL ? (HICON) g_Li.hIconsm : (HICON) hIconsm;
  wc.lpszClassName = (LPCSTR)lpwzClassName;
  wc.cbSize = sizeof(WNDCLASSEXW);
  return RegisterClassExW(reinterpret_cast<const WNDCLASSEXW *>(&wc));
  #else
  #error "Unsupported platform"
  #endif
  return 0;
}

}