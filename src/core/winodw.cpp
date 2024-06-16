//
// Created by 19254 on 24-5-31.
//

#include "HYGUI/Window.h"
#include "HYGUI/Mouse.h"
#include "PrivateDefinition.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_syswm.h>
#include <map>

namespace HYGUI {


bool HYWindowRegisterClass(const HYString &className, const HYString &iconPath, const HYString &cursorPath) {
#ifdef _HOST_WINDOWS_
  WNDCLASSEXW WndClass = {0};
  WndClass.cbSize = sizeof(WNDCLASSEXW);
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  WndClass.lpfnWndProc = DefWindowProc;
  WndClass.hInstance = (HINSTANCE)
    g_app.Instance;
  if (cursorPath.empty()) {
    WndClass.hCursor = g_app.Cursor ? (HCURSOR) g_app.Cursor : LoadCursorW(nullptr,
                                                                           reinterpret_cast<LPCWSTR>(IDC_ARROW));
  } else {
    WndClass.hCursor = LoadCursorFromFileW(cursorPath.toStdWStringView().data());
  }
  WndClass.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH);
  if (iconPath.empty()) {
    WndClass.hIcon = g_app.Icon ? (HICON) g_app.Icon : LoadIconW(nullptr, reinterpret_cast<LPCWSTR>(IDI_APPLICATION));
    WndClass.hIconSm = g_app.IconSm ? (HICON) g_app.IconSm : LoadIconW(nullptr,
                                                                       reinterpret_cast<LPCWSTR>(IDI_APPLICATION));
  } else {
    WndClass.hIcon = LoadIconW((HINSTANCE)
                                 g_app.Instance, iconPath.toStdWStringView().data());
    WndClass.hIconSm = LoadIconW((HINSTANCE)
                                   g_app.Instance, iconPath.toStdWStringView().data());
  }
  WndClass.lpszClassName = className.toStdWStringView().data();
  return RegisterClassExW(&WndClass);
#elif defined(_HOST_APPLE_)
  return true;
#endif
}


#ifdef _HOST_WINDOWS_


HYWindowHandel HYWindowCreate(HYWindowHandel parent, const HYString &title, int x, int y, int width, int height) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto &debug_app = g_app;
  if (x == WINDOWCREATEPOINT_USEDEFAULT) {
    x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
  }
  if (y == WINDOWCREATEPOINT_USEDEFAULT) {
    y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
  }
//  auto hWnd = CreateWindowExW(WS_EX_LAYERED, g_app.DefaultClassName.toStdWStringView().data(),
//                              title.toStdWStringView().data(),
//                              (WS_OVERLAPPEDWINDOW | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_LAYERED) & ~WS_SYSMENU,
//                              x, y, width,
//                              height, parent ? (HWND) parent->Handle : nullptr,
//                              nullptr, (HINSTANCE) g_app.Instance, nullptr);
  auto sdl_wind = SDL_CreateWindow(title.toStdString().c_str(), x, y, width, height,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);
  if (sdl_wind == nullptr) {
    return nullptr;
  }

  // SDL_ShowWindow(sdl_wind);
//  auto id = SDL_GetWindowID(sdl_wind);
// auto w=  SDL_GetWindowFromID(id);
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  //SDL_SysWMinfo info;
  if (!SDL_GetWindowWMInfo(sdl_wind, &info)) {
    g_app.LastError = SDL_GetError();
    return nullptr;
  };
  auto hWnd = info.info.win.window;
  if (hWnd == nullptr) {
    return nullptr;
  }
  auto window = new HYWindow;
  window->ID = SDL_GetWindowID(sdl_wind);
  window->SDLRenderer = SDL_CreateRenderer(
    sdl_wind, // 关联的窗口
    -1, // 使用默认的驱动索引
    SDL_RENDERER_ACCELERATED // 使用硬件加速
  );
  window->SDLWindow = sdl_wind;
  window->Handle = hWnd;
  SDL_GetWindowPosition(sdl_wind, &window->X, &window->Y);
  SDL_GetWindowSize(sdl_wind, &window->Width, &window->Height);
  window->ClientRect = {0, 0, window->Width, window->Height};

  window->WindowCanvasTarget = info.info.win.hdc;

  if (g_app.WindowsTable.find(window) != g_app.WindowsTable.end()) {
    // ????什么玩意
    delete window;
    return nullptr;
  }
  g_app.WindowsTable.insert(window);
  return window;
}

#endif


void window_paint(HYWindow *windowPtr, SDL_WindowEvent *evevt) {
  SDL_SetRenderDrawColor(windowPtr->SDLRenderer, 0, 0, 0, 0);

  //window_recreate_surface(windowPtr);

  auto canvas = windowPtr->Surface->getCanvas();
  canvas->clear(HYColorRGBToARGBInt(windowPtr->BackGroundColor, 255));
  SkPaint paint;
  paint.setAntiAlias(true);
  // 子组件绘制
  canvas->restore();
  canvas->save();
  for (auto obj: windowPtr->Children) {
    HYObjectSendEvent(windowPtr, obj, HYObjectEvent::HYObjectEvent_Paint, 0, 1);
  }

  SkPixmap pixmap;
  windowPtr->Surface->peekPixels(&pixmap);
  void *pixels;
  int pitch;
  SDL_Texture *sdlTexture = SDL_CreateTexture(windowPtr->SDLRenderer, SDL_PIXELFORMAT_ABGR8888,
                                              SDL_TEXTUREACCESS_STREAMING, windowPtr->Width, windowPtr->Height);
  SDL_LockTexture(sdlTexture, nullptr, &pixels, &pitch);
  std::memcpy(pixels, pixmap.addr(), pixmap.computeByteSize());
  SDL_UnlockTexture(sdlTexture);

  SDL_RenderClear(windowPtr->SDLRenderer);
  SDL_RenderCopy(windowPtr->SDLRenderer, sdlTexture, nullptr, nullptr);
  SDL_RenderPresent(windowPtr->SDLRenderer);
};


std::map<uint32_t, std::function<void(HYWindow *, SDL_WindowEvent *)>> g_win_event_map = {
  {HYWindowEvent::HYWindowEvent_Paint, window_paint},
};


uint32_t HYWindowMessageLoop() {
  const int frameDelay = 1000 / 60;

  Uint32 frameStart;
  Uint32 frameTime;
  auto tic_fps_func = [&]() {
    // 计算帧时间
    frameTime = SDL_GetTicks() - frameStart;

    // 帧率限制
    if (frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  };

  while (!g_app.WindowsTable.empty()) {
    DEFER({
            // 清理无效窗口
            std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
            // 倒序从map删除值为nullptr的元素
            if (!g_app.WindowsTable.empty()) {
              auto it = g_app.WindowsTable.begin();
              while (it != g_app.WindowsTable.end()) {
                if (*it == nullptr) {
                  it = g_app.WindowsTable.erase(it);
                } else {
                  ++it;
                }
              }
            }
          });
    frameStart = SDL_GetTicks();
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      // 退出事件
      break;
    }
    if (event.window.windowID < 1) {
      //tic_fps_func();
      continue;
    }
    auto sdlWindow = SDL_GetWindowFromID(event.window.windowID);
    SDL_SysWMinfo winfo;
    SDL_GetWindowWMInfo(sdlWindow, &winfo);
    auto hWnd = winfo.info.win.window;

    auto window = HYWindowGetWindowFromHandle(hWnd);
    if (!window) {
      // 初始化可能需要修正
      adjustwindow_by_sdl(event.window.windowID, sdlWindow, hWnd);
      window = HYWindowGetWindowFromHandle(hWnd);
      if (!window) {
        continue;
      }
      window_recreate_surface(window);
    }
    if (!window->IsInit) {
      window->IsInit = true;
      if (window->Show) {
        SDL_ShowWindow(sdlWindow);
      }
    }
    if (event.type == SDL_EventType::SDL_WINDOWEVENT) {
      // 窗口事件
      if (event.window.event == SDL_WINDOWEVENT_MOVED) {
        // 窗口移动
        window->X = event.window.data1;
        window->Y = event.window.data2;
      }

    } else if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
      // 鼠标按键按下事件
      if (event.button.button == SDL_BUTTON_LEFT) {
        // 左键被按下
        if (event.button.y < window->TitleBarHeight) {
          // 准备移动窗口
          window->Drag = true;
          auto wp = HYMouseGetPosition();
          window->oldMousePoint = {wp.x,wp.y};
          window->oldWinPoint = {window->X, window->Y};
        } else {
          // 通知子组件
          // HYObjectSendEventLIst(window, HYObjectEvent::HYObjectEvent_MouseMove, 0, HYPointGenLParam(event.button.x, event.button.y));
        }

      }
    } else if (event.type == SDL_EventType::SDL_MOUSEBUTTONUP) {
      // 鼠标按键抬起事件
      window->Drag = false;
      window->oldWinPoint = {0, 0};
      window->oldMousePoint = {0, 0};

    } else if (event.type == SDL_EventType::SDL_MOUSEMOTION) {
      // 鼠标移动事件
      // event.motion.type = SDL_MOUSEMOTION;
      if (window->Drag) {
        // 移动窗口
        auto wp = HYMouseGetPosition();
        window->X = window->oldWinPoint.x + wp.x - window->oldMousePoint.x;
        window->Y = window->oldWinPoint.y + wp.y - window->oldMousePoint.y;
        SDL_SetWindowPosition(sdlWindow, window->X, window->Y);
        // 移动窗口不要限制帧率
        continue;

      } else {
        auto obj = HYObjectObjFromMousePos(window, event.button.x, event.button.y);
        if (obj) {
          // 转换坐标
          auto [x1,y1] = HYObjectGetRelativePoint(obj, event.button.x, event.button.y);
          HYObjectSendEvent(window, obj, HYObjectEvent_MouseMove, 0, HYPointGenLParam(x1, y1));
        }
        // HYObjectSendEventLIst(window, HYObjectEvent::HYObjectEvent_MouseMove, 0, HYPointGenLParam(event.button.x, event.button.y));
      }


      //HYObjectSendEventLIst

    } else if (event.type == g_app.EventWindow) {
      // 自定义窗口事件
      auto iter = g_win_event_map.find(event.window.event);
      if (iter != g_win_event_map.end())
        iter->second(window, &event.window);

    }

    //tic_fps_func();
  }
  return 0;
}

void HYWindowUserDataAdd(HYWindowHandel window, intptr_t key, intptr_t data) {
  window->UserData[key] = data;
};

void HYWindowUserDataRemove(HYWindowHandel window, intptr_t key,
                            const std::function<
                              bool(HYWindowHandel window, intptr_t key, intptr_t value)
                            > &callback) {

  if (window->UserData.find(key) != window->UserData.end()) {
    if (!callback ||
        callback(window, key, window->UserData[key])) {
      window->UserData.erase(key);
    }
  }
}

HYWindow *HYWindowGetWindowFromHandle(WINDOWHANDEL handle) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto &debug_app = g_app;
  if (!g_app.WindowsTable.empty()) {
    for (auto &iter: g_app.WindowsTable) {
      if (iter->Handle == handle) {
        return iter;
      }
    }
  }

  return nullptr;
}

void HYWindowShow(HYWindow *wind) {
  wind->Show = true;
  if (wind->IsInit) {
    SDL_ShowWindow(wind->SDLWindow);
  }
}


}

