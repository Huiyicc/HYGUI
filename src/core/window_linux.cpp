//
// Created by huiyi on 24-6-22.
//
#ifdef _HOST_LINUX_

#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include "SDL3/SDL.h"

namespace HYGUI {

void window_hook_handel(HYWindow *windowPtr) {

}

void adjustwindow_by_sdl(HYWindowHandel window, void *newhandel) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  window->Handle.handle = newhandel;
  SDL_GetWindowPosition(window->SDLWindow, &window->X, &window->Y);
  SDL_GetWindowSize(window->SDLWindow, &window->Width, &window->Height);
  window->ClientRect = {0, 0, window->Width, window->Height};
  window_hook_handel(window);
}

}

#endif
