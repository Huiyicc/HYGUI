//
// Created by 19254 on 24-5-31.
//

#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>
#include <gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLAssembleInterface.h>
#include <map>
#include <mutex>
#include "HYGUI/Font.h"
#include "HYGUI/Mouse.h"
#include "HYGUI/Object.h"
#include "HYGUI/Window.h"
#include "PrivateDefinition.h"

#include "include/core/SkFont.h"

namespace HYGUI {
HYWindow::~HYWindow() {
  for (auto obj: Children) {
    delete obj;
  }
  if (CursorMap.empty()) {
    for (auto &[key, value]: CursorMap) {
      SDL_FreeCursor((SDL_Cursor *) value);
    }
  }
  if (GrCtx) {
    HYResourceRemove(ResourceType::ResourceType_Other, GrCtx);
    GrCtx = nullptr;
  }
  if (Surface) {
    HYResourceRemove(ResourceType::ResourceType_Other, Surface);
    GrCtx = nullptr;
  }
  if (SDLOpenGl) {
    HYResourceRemove(ResourceType::ResourceType_Other, SDLOpenGl);
    SDLOpenGl = nullptr;
  }
  if (SDLWindow) {
    HYResourceRemove(ResourceType::ResourceType_Window, SDLWindow);
    SDLWindow = nullptr;
  }
  HYResourceRemove(ResourceType::ResourceType_Window, this);
}

void HYWindowDestroy(HYWindowHandel wnd) {
  if (!wnd->Handle) { return; }
  g_app.WindowsTable.erase(wnd);
  delete wnd;
}

GrGLFuncPtr glgetpoc(void *ctx, const char name[]) {
  return (GrGLFuncPtr) SDL_GL_GetProcAddress(name);
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
                                   SDL_WINDOW_OPENGL           // opengl
                                     | SDL_WINDOW_ALLOW_HIGHDPI// 高dpi
                                     | SDL_WINDOW_HIDDEN       // 隐藏
                                     | SDL_WINDOW_RESIZABLE    // 可调整大小
                                     | SDL_WINDOW_BORDERLESS   // 无边框
  );

  if (sdl_wind == nullptr) {
    return nullptr;
  }
  HYResourceRegister(ResourceType::ResourceType_Window, sdl_wind, "sdl window", [](void *resource) {
    SDL_DestroyWindow((SDL_Window *) resource);
  });
  // 创建OpenGL上下文
  SDL_GLContext glContext = SDL_GL_CreateContext(sdl_wind);
  if (glContext == nullptr) {
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    return nullptr;
  }
  HYResourceRegisterOther(glContext, "SDL_GLContext", [](void *resource) {
    SDL_GL_DeleteContext((SDL_GLContext) resource);
  });
  // 切换到OpenGL上下文
  int success = SDL_GL_MakeCurrent(sdl_wind, glContext);
  if (success != 0) {
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    return nullptr;
  }
  static const int kMsaaSampleCount = 0;//4;

  int contextType;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextType);
  int dw, dh;
  SDL_GL_GetDrawableSize(sdl_wind, &dw, &dh);
  glViewport(0, 0, dw, dh);
  glClearColor(1, 1, 1, 1);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // 准备GrContext
  auto skInterface = GrGLMakeNativeInterface();
  if (!skInterface) {
    skInterface = GrGLMakeAssembledInterface(
      nullptr, glgetpoc);
  }

  if (!skInterface) {
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    return nullptr;
  }
  // 准备contexts
  sk_sp<GrDirectContext> grContext(GrDirectContexts::MakeGL(skInterface));
  if (!grContext) {
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    return nullptr;
  }

  auto window = new HYWindow;
  window->GrCtx = HYResourceRegisterOther(grContext.release(), "GrDirectContext", [](void *resource) {
    SkSafeUnref((GrDirectContext *) resource);
  });
  window->SDLOpenGl = glContext;
  window->ID = SDL_GetWindowID(sdl_wind);
  window->SDLWindow = sdl_wind;
  window->ClientRect = {0, 0, dw, dh};
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  if (!SDL_GetWindowWMInfo(sdl_wind, &info)) {
    g_app.LastError = SDL_GetError();
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    HYResourceRemove(ResourceType::ResourceType_Other, window->GrCtx);
    delete window;
    return nullptr;
  };
#ifdef _HOST_WINDOWS_
  auto hWnd = info.info.win.window;
#elif defined(_HOST_APPLE_)
  auto hWnd = info.info.cocoa.window;
#elif defined(_HOST_LINUX_)
  auto hWnd = info.info.x11.window;
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

  if (g_app.WindowsTable.find(window) != g_app.WindowsTable.end()) {
    // ????什么玩意
    delete window;
    return nullptr;
  }
  g_app.WindowsTable.insert(window);
  HYResourceRegister(ResourceType::ResourceType_Window, window, "hywindow", [](void *resource) {
    delete (HYWindow *) resource;
  });
  return window;
}


void window_paint(HYWindow *windowPtr, SDL_WindowEvent *evevt) {
  // 切换到OpenGL上下文
  SDL_GL_MakeCurrent(windowPtr->SDLWindow, windowPtr->SDLOpenGl);
  auto canvas = windowPtr->Surface->getCanvas();
  canvas->clear(HYColorRGBToARGBInt(windowPtr->BackGroundColor, 255));

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

int getMouseCursorType(HYWindow *window, int x, int y, int edge = 5) {
  int dragType = HY_SYSTEM_CURSOR_ARROW;
  if (x <= edge) {
    if (y <= edge) {
      // 左上角
      dragType = HY_SYSTEM_CURSOR_SIZENWSE;
    } else if (y >= window->Height - edge) {
      // 左下角
      dragType = HY_SYSTEM_CURSOR_SIZENESW;
    } else {
      // 左边缘
      dragType = HY_SYSTEM_CURSOR_SIZEWE;
    }
  } else if (x >= window->Width - edge) {
    if (y <= edge) {
      // 右上角
      dragType = HY_SYSTEM_CURSOR_SIZENESW;
      window->DragType1 = 1;
    } else if (y >= window->Height - edge) {
      // 右下角
      dragType = HY_SYSTEM_CURSOR_SIZENWSE;
      window->DragType1 = 1;
    } else {
      // 右边缘
      dragType = HY_SYSTEM_CURSOR_SIZEWE;
      window->DragType1 = 1;
    }
  } else if (y <= edge) {
    // 上边缘
    dragType = HY_SYSTEM_CURSOR_SIZENS;
  } else if (y >= window->Height - edge) {
    // 下边缘
    dragType = HY_SYSTEM_CURSOR_SIZENS;
    window->DragType1 = 1;
  } else {
    // 恢复默认
    dragType = HY_SYSTEM_CURSOR_ARROW;
    window->DragType1 = 0;
  }
  return dragType;
}

int handleMouseButtonDown(SDL_Event *event, HYWindow *window) {
  // 鼠标按键按下事件
  if (event->button.button == SDL_BUTTON_LEFT) {
    // 左键被按下
    auto dragType = getMouseCursorType(window, event->button.x, event->button.y);
    if ((event->button.y < window->TitleBarHeight && event->button.y > 0) || dragType != HY_SYSTEM_CURSOR_ARROW) {
      // 准备移动窗口
      window->Drag = true;
      window->DragType = dragType == HY_SYSTEM_CURSOR_ARROW ? 0 : dragType;
      auto wp = HYMouseGetPosition();
      window->oldMousePoint = {wp.x, wp.y};
      window->oldWinRect = {window->X, window->Y, window->Width, window->Height};
    } else {
      // 通知子组件
      window->Drag = false;
      window->DragType = 0;
    }
  }
  return 0;
}

int handleMouseButtonUp(SDL_Event *event, HYWindow *window) {
  window->Drag = false;
  window->DragType = 0;
  window->oldWinRect = {0, 0, 0, 0};
  window->oldMousePoint = {0, 0};
  return 0;
}

int handleMouseMotion(SDL_Event *event, HYWindow *window) {
  // 鼠标移动事件
  if (window->Drag) {
    if (window->DragType == 0) {
      // 移动窗口
      auto wp = HYMouseGetPosition();
      window->X = window->oldWinRect.x + wp.x - window->oldMousePoint.x;
      window->Y = window->oldWinRect.y + wp.y - window->oldMousePoint.y;
      SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
    } else if (window->DragType == HY_SYSTEM_CURSOR_SIZENWSE) {
      // 处于左上/右下角调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->DragType1 == 0) {
        // 左上角
        window->X = window->oldWinRect.x + wp.x - window->oldMousePoint.x;
        window->Y = window->oldWinRect.y + wp.y - window->oldMousePoint.y;
        window->Width = window->oldWinRect.width + window->oldWinRect.x - window->X;
        window->Height = window->oldWinRect.height + window->oldWinRect.y - window->Y;
        SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      } else {
        // 右下角
        window->Width = window->oldWinRect.width + wp.x - window->oldMousePoint.x;
        window->Height = window->oldWinRect.height + wp.y - window->oldMousePoint.y;
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      }

    } else if (window->DragType == HY_SYSTEM_CURSOR_SIZENESW) {
      // 处于左下/右上角调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->DragType1 == 0) {
        // 左下角
        window->X = window->oldWinRect.x + wp.x - window->oldMousePoint.x;
        window->Width = window->oldWinRect.width + window->oldWinRect.x - window->X;
        window->Height = window->oldWinRect.height + wp.y - window->oldMousePoint.y;
        SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      } else {
        // 右上角
        window->Y = window->oldWinRect.y + wp.y - window->oldMousePoint.y;
        window->Width = window->oldWinRect.width + wp.x - window->oldMousePoint.x;
        window->Height = window->oldWinRect.height + window->oldWinRect.y - window->Y;
        SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      }
    } else if (window->DragType == HY_SYSTEM_CURSOR_SIZEWE) {
      // 处于左右边缘调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->DragType1 == 0) {
        // 左边缘
        window->X = window->oldWinRect.x + wp.x - window->oldMousePoint.x;
        window->Width = window->oldWinRect.width + window->oldWinRect.x - window->X;
        SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      } else {
        // 右边缘
        window->Width = window->oldWinRect.width + wp.x - window->oldMousePoint.x;
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      }

    } else if (window->DragType == HY_SYSTEM_CURSOR_SIZENS) {
      // 处于上下边缘调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->DragType1 == 0) {
        // 上边缘
        window->Y = window->oldWinRect.y + wp.y - window->oldMousePoint.y;
        window->Height = window->oldWinRect.height + window->oldWinRect.y - window->Y;
        SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      } else {
        // 下边缘
        window->Height = window->oldWinRect.height + wp.y - window->oldMousePoint.y;
        SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
      }

    } else if (window->DragType == HY_SYSTEM_CURSOR_SIZENWSE) {
      // 处于左下角调整窗口尺寸
      auto wp = HYMouseGetPosition();
      window->X = window->oldWinRect.x + wp.x - window->oldMousePoint.x;
      window->Width = window->oldWinRect.width + window->oldWinRect.x - window->X;
      window->Height = window->oldWinRect.height + window->oldWinRect.y - window->Y;
      SDL_SetWindowPosition(window->SDLWindow, window->X, window->Y);
      SDL_SetWindowSize(window->SDLWindow, window->Width, window->Height);
    }
    return 1;
  } else {
    int x = event->motion.x;
    int y = event->motion.y;
    auto dragType = getMouseCursorType(window, x, y);
    SDL_SetCursor((SDL_Cursor *) window->CursorMap[dragType]);
    window->DragType = dragType;

    auto obj = HYObjectObjFromMousePos(window, event->button.x, event->button.y);
    if (obj) {
      // 转换坐标
      auto [x1, y1] = HYObjectGetRelativePoint(obj, event->button.x, event->button.y);
      HYObjectSendEvent(window, obj, HYObjectEvent_MouseMove, 0, HYPointGenLParam(x1, y1));
    }
  }
  return 0;
}

void HYWindowSkinHook(HYWindow *wnd, HYRGB backGroundColor, int diaphaneity) {
  wnd->EventQueue.SetProcessCallback(processing_object_event);

  wnd->BackGroundColor = HYColorRGBToInt(backGroundColor);
  wnd->Diaphaneity = diaphaneity;

  if (wnd->CursorMap.empty()) {
    for (auto &[key, value]: wnd->CursorMap) {
      HYResourceRemove(ResourceType::ResourceType_Cursor, value);
    }
  }
  wnd->CursorMap.clear();
  static std::vector<HY_SYSTEM_CURSOR> cursors = {
    HY_SYSTEM_CURSOR_ARROW,
    HY_SYSTEM_CURSOR_IBEAM,
    HY_SYSTEM_CURSOR_WAIT,
    HY_SYSTEM_CURSOR_CROSSHAIR,
    HY_SYSTEM_CURSOR_WAITARROW,
    HY_SYSTEM_CURSOR_SIZENWSE,
    HY_SYSTEM_CURSOR_SIZENESW,
    HY_SYSTEM_CURSOR_SIZEWE,
    HY_SYSTEM_CURSOR_SIZENS,
    HY_SYSTEM_CURSOR_SIZEALL,
    HY_SYSTEM_CURSOR_NO,
    HY_SYSTEM_CURSOR_HAND,
  };
  for (auto cursor: cursors) {
    wnd->CursorMap[cursor] = HYResourceRegister(ResourceType::ResourceType_Cursor,
                                                SDL_CreateSystemCursor((SDL_SystemCursor) cursor),
                                                "sdl cursor", [](void *resource) {
                                                  SDL_FreeCursor((SDL_Cursor *) resource);
                                                });
  }

  SDL_SetWindowOpacity(wnd->SDLWindow, (float) (diaphaneity) / 255.0f);
  window_recreate_surface(wnd);
}

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
    auto hWnd = winfo.info.cocoa.window;
#elif defined(_HOST_LINUX_)
    auto hWnd = winfo.info.x11.window;
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
        //        window->X = event.window.data1;
        //        window->Y = event.window.data2;
        SDL_GetWindowPosition(sdlWindow, &window->X, &window->Y);
      } else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        // 窗口大小改变
        window_recreate_surface(window);
      }
    } else if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
      // 鼠标按键按下事件
      if (handleMouseButtonDown(&event, window) != 0) {
        continue;
      }
    } else if (event.type == SDL_EventType::SDL_MOUSEBUTTONUP) {
      // 鼠标按键抬起事件
      if (handleMouseButtonUp(&event, window) != 0) {
        continue;
      }

    } else if (event.type == SDL_EventType::SDL_MOUSEMOTION) {
      // 鼠标移动事件
      if (handleMouseMotion(&event, window) != 0) {
        continue;
      }
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
                              bool(HYWindowHandel window, intptr_t key, intptr_t value)> &callback) {
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

void HYWindowSendEventRePaint(HYWindow *wind) {
  SDL_Event event;
  event.type = g_app.EventWindow;
  event.window.windowID = wind->ID;
  event.window.event = HYWindowEvent_Paint;
  event.window.data1 = 0;
  event.window.data2 = 0;
  SDL_PushEvent(&event);
}

}// namespace HYGUI
