//
// Created by 回忆 on 24-10-6.
//
#include "PrivateDefinition.h"


namespace HYGUI {

void window_hook_handel(HYWindow *windowPtr) {

}

void adjustwindow_by_sdl(HYWindow* window, void *newhandel) {
  // std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  // HWND hWnd = (HWND) newhandel;
  // window->Handle.handle = hWnd;
  // SDL_GetWindowPosition(window->SDLWindow, &window->X, &window->Y);
  // SDL_GetWindowSize(window->SDLWindow, &window->Width, &window->Height);
  // window->ClientRect = {0, 0, window->Width, window->Height};
  // window_hook_handel(window);
}

}