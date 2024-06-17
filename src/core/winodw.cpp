//
// Created by 19254 on 24-5-31.
//

#include "HYGUI/Window.h"
#include "HYGUI/Mouse.h"
#include "PrivateDefinition.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_syswm.h>
#include <map>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include "include/gpu/gl/GrGLInterface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include <SDL2/SDL_opengl.h>
#include <gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLAssembleInterface.h>

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


HYWindowHandel HYWindowCreate(HYWindowHandel parent, const HYString &title, int x, int y, int width, int height) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);

  SDL_DisplayMode dsinfo;
  SDL_GetDesktopDisplayMode(0, &dsinfo);
  if (x == WINDOWCREATEPOINT_USEDEFAULT) {
    x = (dsinfo.w - width) / 2;
  }
  if (y == WINDOWCREATEPOINT_USEDEFAULT) {
    y = (dsinfo.h - height) / 2;
  }

  auto sdl_wind = SDL_CreateWindow(title.toStdString().c_str(), x, y, width, height,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);
  if (sdl_wind == nullptr) {
    return nullptr;
  }
  // 创建OpenGL上下文
  SDL_GLContext glContext = SDL_GL_CreateContext(sdl_wind);
  if (glContext == nullptr) {
    SDL_DestroyWindow(sdl_wind);
    return nullptr;
  }

  // 设置OpenGL属性
  int success = SDL_GL_MakeCurrent(sdl_wind, glContext);
  if (success != 0) {
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DeleteContext(glContext);
    return nullptr;
  }
  static const int kMsaaSampleCount = 0; //4;

  // 获取窗口像素格式
  uint32_t windowFormat = SDL_GetWindowPixelFormat(sdl_wind);
  int contextType;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextType);
  int dw, dh;
  SDL_GL_GetDrawableSize(sdl_wind, &dw, &dh);
  glViewport(0, 0, dw, dh);
  glClearColor(1, 1, 1, 1);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // 准备GrContext
  // auto skInterface = GrGLMakeNativeInterface();
  auto skInterface = GrGLMakeAssembledInterface(
    nullptr, (GrGLGetProc) * [](void*, const char* p) -> void* { return (void*)SDL_GL_GetProcAddress(p); });
  if (!skInterface) {
    SDL_DestroyWindow(sdl_wind);
    return nullptr;
  }
  // 准备contexts
  sk_sp<GrDirectContext> grContext(GrDirectContexts::MakeGL(skInterface));
  if (!grContext) {
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DeleteContext(glContext);
    return nullptr;
  }

//  GrBackend backend = GrBackend::kOpenGL_GrBackend;
//  GrContextOptions options;
//  auto dContext = GrDirectContexts::MakeGL(skInterface, options);
// // auto dContext = GrDirectContexts::MakeGL();
//  if (!dContext) {
//    SDL_DestroyWindow(sdl_wind);
//    return nullptr;
//  }

  // auto skCtx = GrDirectContexts::MakeGL(skInterface);

  auto window = new HYWindow;
  window->GrCtx = grContext.release();
  window->SDLGl = glContext;
  window->ID = SDL_GetWindowID(sdl_wind);
  window->SDLRenderer = SDL_CreateRenderer(
    sdl_wind, // 关联的窗口
    -1, // 使用默认的驱动索引
    SDL_RENDERER_ACCELERATED // 使用硬件加速
  );
  window->SDLWindow = sdl_wind;
  window->ClientRect={0,0,dw,dh};
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  if (!SDL_GetWindowWMInfo(sdl_wind, &info)) {
    g_app.LastError = SDL_GetError();
    SDL_DestroyWindow(sdl_wind);
    grContext->unref();
    delete window;
    return nullptr;
  };
#ifdef _HOST_WINDOWS_
  auto hWnd = info.info.win.window;
#elif defined(_HOST_APPLE_)
  auto hWnd = info.info.cocoa.window;
#else
#error "Not support"
#endif
  if (hWnd == nullptr) {
    return nullptr;
  }

  window->Handle = hWnd;
  SDL_GetWindowPosition(sdl_wind, &window->X, &window->Y);
  SDL_GetWindowSize(sdl_wind, &window->Width, &window->Height);
  window->ClientRect = {0, 0, window->Width, window->Height};
#ifdef _HOST_WINDOWS_
  window->WindowCanvasTarget = info.info.win.hdc;
#elif defined(_HOST_APPLE_)
  window->WindowCanvasTarget = info.info.cocoa.window;
#else
#error "Not support"
#endif

  if (g_app.WindowsTable.find(window) != g_app.WindowsTable.end()) {
    // ????什么玩意
    delete window;
    return nullptr;
  }
  g_app.WindowsTable.insert(window);
  return window;
}


void window_paint(HYWindow *windowPtr, SDL_WindowEvent *evevt) {
//  SDL_SetRenderDrawColor(windowPtr->SDLRenderer, 0, 0, 0, 255);
//  SDL_RenderClear(windowPtr->SDLRenderer);

  auto canvas = windowPtr->Surface->getCanvas();
  canvas->clear(HYColorRGBToARGBInt(windowPtr->BackGroundColor, 255));
  SkPaint paint;
  paint.setAntiAlias(true);
  // 子组件绘制
  canvas->restore();
  canvas->save();
  for (auto obj: windowPtr->Children) {
    // 子组件绘制
    HYObjectSendEvent(windowPtr, obj, HYObjectEvent::HYObjectEvent_Paint, 0, 1);
  }

  ((GrDirectContext *) windowPtr->GrCtx)->flush(windowPtr->Surface);

  // 将绘制的内容显示到窗口


  SDL_GL_SwapWindow(windowPtr->SDLWindow);

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
    #ifdef _HOST_WINDOWS_
    auto hWnd = winfo.info.win.window;
    #elif defined(_HOST_APPLE_)
    auto hWnd =winfo.info.cocoa.window;
    #endif


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
          window->oldMousePoint = {wp.x, wp.y};
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
          auto [x1, y1] = HYObjectGetRelativePoint(obj, event.button.x, event.button.y);
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

