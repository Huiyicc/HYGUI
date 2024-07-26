//
// Created by 19254 on 24-5-31.
//

#include "HYGUI/Font.h"
#include "HYGUI/Mouse.h"
#include "HYGUI/Object.h"
#include "HYGUI/Paint.h"
#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include "include/core/SkRRect.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_system.h>
#include <gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLAssembleInterface.h>
#include <map>
#include <mutex>
#ifdef _HOST_LINUX_
#include <X11/Xlib.h>
#endif

#include "SDL3/SDL.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/gl/GrGLTypes.h"
#include <HYGUI/Utils.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_system.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>
#include <src/gpu/ganesh/gl/GrGLDefines.h>

namespace HYGUI {
HYWindow::~HYWindow() {
  EventQueue.Stop();
  for (auto obj: Children) {
    HYResourceRemove(ResourceType::ResourceType_Object, obj);
  }
  Children.clear();
  if (!CursorMap.empty()) {
    for (auto &[key, value]: CursorMap) {
      HYResourceRemove(ResourceType::ResourceType_Cursor, value);
    }
  }
  if (SDLOpenGl) {
    HYResourceRemove(ResourceType::ResourceType_Other, SDLOpenGl);
    SDLOpenGl = nullptr;
  }
  if (SDLWindow) {
    HYResourceRemove(ResourceType::ResourceType_Window, SDLWindow);
    SDLWindow = nullptr;
  }
  if (Surface) {
    HYResourceRemove(ResourceType::ResourceType_Other, Surface);
    Surface = nullptr;
  }
  if (GrCtx) {
    HYResourceRemove(ResourceType::ResourceType_Other, GrCtx);
    GrCtx = nullptr;
  }
}

void HYWindowDestroy(HYWindowHandel wnd) {
  if (!wnd->Handle.handle) { return; }
  std::lock_guard<std::mutex> lock_lookup(g_app.LookupLock);
  std::lock_guard<std::mutex> lock_table(g_app.WindowsTableMutex);

  g_app.WindowsTable.erase(wnd);
  HYResourceRemove(ResourceType::ResourceType_Window, wnd);
  SDL_DestroyWindow(wnd->SDLWindow);
}

GrGLFuncPtr glgetpoc(void *ctx, const char name[]) {
  return (GrGLFuncPtr) SDL_GL_GetProcAddress(name);
}

HYWindowHandel HYWindowCreate(HYWindowHandel parent, const HYString &title, int x, int y, int width, int height) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);

  auto dsinfo = SDL_GetDesktopDisplayMode(1);
  if (x == WINDOWCREATEPOINT_USEDEFAULT) {
    x = (dsinfo->w - width) / 2;
  }
  if (y == WINDOWCREATEPOINT_USEDEFAULT) {
    y = (dsinfo->h - height) / 2;
  }
  // if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) != 0) {
  //   PrintDebug("{}", SDL_GetError());
  // }
  auto sdl_wind = SDL_CreateWindow(title.toStdString().c_str(), width, height,
                                   SDL_WINDOW_OPENGL                // opengl
                                     | SDL_WINDOW_HIGH_PIXEL_DENSITY// 高dpi
                                     //                                     | SDL_WINDOW_HIDDEN       // 隐藏
                                     | SDL_WINDOW_RESIZABLE // 可调整大小
                                     | SDL_WINDOW_BORDERLESS// 无边框
                                     | SDL_WINDOW_TRANSPARENT);
  if (sdl_wind == nullptr) {
    return nullptr;
  }

  SDL_HideWindow(sdl_wind);
  HYResourceRegister(ResourceType::ResourceType_Window, sdl_wind, "sdl window", [](void *resource) {
    std::lock_guard<std::mutex> look_up_lock(g_app.LookupLock);
    SDL_DestroyWindow((SDL_Window *) resource);
  });

  // 创建OpenGL上下文
  SDL_GLContext glContext = SDL_GL_CreateContext(sdl_wind);
  if (glContext == nullptr) {
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    return nullptr;
  }
  HYResourceRegisterOther(glContext, "SDL_GLContext", [](void *resource) {
    SDL_GL_DestroyContext((SDL_GLContext) resource);
  });
  // 切换到OpenGL上下文
  int success = SDL_GL_MakeCurrent(sdl_wind, glContext);
  if (success != 0) {
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    return nullptr;
  }
  // auto opengl_buffer = SDL_GetProperty(SDL_GetWindowProperties(sdl_wind), SDL_PROP_WINDOW_UIKIT_OPENGL_FRAMEBUFFER_NUMBER, nullptr);
  // glEnable(GL_MULTISAMPLE);
  static const int kMsaaSampleCount = 0;//4;

  int contextType;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextType);
  //  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
  int dw, dh;
  SDL_GetWindowSizeInPixels(sdl_wind, &dw, &dh);
  glViewport(0, 0, dw, dh);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

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
  auto grctx = grContext.release();
  window->GrCtx = HYResourceRegisterOther(grctx, "GrDirectContext", [](void *resource) {
    auto ctx = (GrDirectContext *) resource;
    ctx->abandonContext();
    SkSafeUnref(ctx);
  });
  //window->GrCtx = HYResourceRegisterOther(grctx, "GrDirectContext", nullptr);
  window->SDLOpenGl = glContext;
  window->ID = SDL_GetWindowID(sdl_wind);
  window->SDLWindow = sdl_wind;
  window->ClientRect = {0, 0, dw, dh};

  auto hWnd = HYWindowGetHandel(window);
  if (hWnd.handle == nullptr) {
    g_app.LastError = "Create window fail";
    HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    HYResourceRemove(ResourceType::ResourceType_Other, window->GrCtx);
    delete window;
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
  HYResourceRemoveClearFunc(ResourceType::ResourceType_Window, sdl_wind);
  return window;
}


void window_paint(HYWindow *windowPtr, void *evevt) {
  // 切换到OpenGL上下文
  SDL_GL_MakeCurrent(windowPtr->SDLWindow, (SDL_GLContext) windowPtr->SDLOpenGl);

  auto canvas = windowPtr->Surface->getCanvas();
  // 透明背景
  SkRRect roundRect;
  roundRect.setRectXY(SkRect::MakeXYWH(0, 0, windowPtr->Width, windowPtr->Height),
                      windowPtr->round, windowPtr->round);
  canvas->clipRRect(roundRect);

  SkPaint bgpaint;
  bgpaint.setColor(HYColorRGBToARGBInt(windowPtr->BackGroundColor, 255));
  // 白色
  bgpaint.setAntiAlias(true);
  canvas->drawRect(SkRect::MakeLTRB(0, 0, windowPtr->ClientRect.width, windowPtr->ClientRect.height),
                   bgpaint);

  // 子组件绘制
  canvas->save();
  for (auto obj: windowPtr->Children) {
    // 子组件绘制
    HYObjectPushEventCall(windowPtr, obj, HYObjectEvent::HYObjectEvent_Paint, 0, 1);
  }

  canvas->restore();
  canvas->resetMatrix();

  ((GrDirectContext *) windowPtr->GrCtx)->flush(windowPtr->Surface);

  // 将绘制的内容显示到窗口
  SDL_GL_SwapWindow(windowPtr->SDLWindow);
};


std::map<uint32_t, std::function<void(HYWindow *, void *)>> g_win_event_map = {
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
  auto push_event = HYObjectEvent::HYObjectEvent_LeftDown;
  if (event->button.button == SDL_BUTTON_LEFT) {
    // 左键被按下
    push_event = HYObjectEvent::HYObjectEvent_LeftDown;
  } else if (event->button.button == SDL_BUTTON_RIGHT) {
    // 右键被按下
    push_event = HYObjectEvent::HYObjectEvent_RightDown;
  } else if (event->button.button == SDL_BUTTON_MIDDLE) {
    // 中键被按下
    push_event = HYObjectEvent::HYObjectEvent_MiddleDown;
  }
  auto dragType = getMouseCursorType(window, event->button.x, event->button.y);
  if ((event->button.y < window->TitleBarHeight && event->button.y > 0) || dragType != HY_SYSTEM_CURSOR_ARROW) {
    // 准备移动窗口
    window->Drag = true;
    window->DragType = dragType == HY_SYSTEM_CURSOR_ARROW ? 0 : dragType;
    auto wp = HYMouseGetPosition();
    window->oldMousePoint = {int(wp.x), int(wp.y)};
    window->oldWinRect = {window->X, window->Y, window->Width, window->Height};

    window->LastEventObject = window->CurrentEventObject;
    window->LastEventObjectTime = window->CurrentEventObjectTime;
    window->CurrentEventObject = nullptr;
    window->CurrentEventObjectTime = event->button.timestamp;

  } else {
    // 通知子组件
    window->Drag = false;
    window->DragType = 0;
    auto act_obj = HYObjectGetFromMousePos(window, event->button.x, event->button.y);
    if (act_obj) {
      if (push_event == HYObjectEvent::HYObjectEvent_LeftDown) {
        // 组件获取焦点
        HYObjectSetFocus(act_obj, true);
      }
      // 转换坐标
      auto [x1, y1] = HYObjectGetRelativePoint(act_obj, event->button.x, event->button.y);
      HYObjectPushEventCall(window, act_obj, push_event, 0, HYPointGenWParam(x1, y1));
    } else {
      if (window->FocusObject) {
        // 释放焦点
        HYObjectSetFocus(window->FocusObject, false);
      }
    }
  }
  return 0;
}

int handleMouseButtonUp(SDL_Event *event, HYWindow *window) {
  // 鼠标按键放开
  auto push_event = HYObjectEvent::HYObjectEvent_LeftUp;
  if (event->button.button == SDL_BUTTON_LEFT) {
    // 左键被按下
    push_event = HYObjectEvent::HYObjectEvent_LeftUp;
  } else if (event->button.button == SDL_BUTTON_RIGHT) {
    // 右键被按下
    push_event = HYObjectEvent::HYObjectEvent_RightUp;
  } else if (event->button.button == SDL_BUTTON_MIDDLE) {
    // 中键被按下
    push_event = HYObjectEvent::HYObjectEvent_MiddleUp;
  }
  auto dragType = getMouseCursorType(window, event->button.x, event->button.y);
  if ((event->button.y < window->TitleBarHeight && event->button.y > 0) || dragType != HY_SYSTEM_CURSOR_ARROW) {
    // 准备移动窗口
    window->Drag = false;
    window->DragType = 0;
    window->oldWinRect = {0, 0, 0, 0};
    window->oldMousePoint = {0, 0};
  } else {
    // 通知子组件
    window->Drag = false;
    window->DragType = 0;
    window->oldWinRect = {0, 0, 0, 0};
    window->oldMousePoint = {0, 0};
    auto act_obj = HYObjectGetFromMousePos(window, event->button.x, event->button.y);
    if (act_obj) {
      // 转换坐标
      auto [x1, y1] = HYObjectGetRelativePoint(act_obj, event->button.x, event->button.y);
      HYObjectPushEventCall(window, act_obj, push_event, 0, HYPointGenWParam(x1, y1));
    }
  }
  return 0;
}

int handleMouseWheel(SDL_Event *event, HYWindow *window) {
  // 屏幕坐标转窗口坐标
  auto [bx, by] = HYMouseGetPositionFromWindow(window);
  auto obj = HYObjectGetFromMousePos(window, bx, by);
  if (obj) {
    auto lp = HYPointfGenWParam(event->wheel.x, event->wheel.y);
    HYObjectPushEventCall(window, obj, HYObjectEvent::HYObjectEvent_MouseWheel, 0, lp);
  }
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

    auto obj = HYObjectGetFromMousePos(window, event->button.x, event->button.y);
    if (obj) {
      if (window->CurrentEventObject != obj) {
        if (window->CurrentEventObject) {
          // 退出事件
          HYObjectPushEventCall(window, window->CurrentEventObject, HYObjectEvent::HYObjectEvent_MouseLeave, 0, 0);
        }
        window->HoverObject = obj;
        // 进入事件
        HYObjectPushEventCall(window, obj, HYObjectEvent::HYObjectEvent_MouseEnter, 0, 0);
      }
      // 转换坐标
      auto [x1, y1] = HYObjectGetRelativePoint(obj, event->button.x, event->button.y);
      HYObjectPushEventCall(window, obj, HYObjectEvent_MouseMove, 0, HYPointGenWParam(x1, y1));
    } else {
      if (window->CurrentEventObject && window->HoverObject) {
        // 退出事件
        auto hoverObj = window->HoverObject;
        window->HoverObject = nullptr;
        HYObjectPushEventCall(window, hoverObj, HYObjectEvent::HYObjectEvent_MouseLeave, 0, 0);
        window->LastEventObject = window->CurrentEventObject;
        window->LastEventObjectTime = window->CurrentEventObjectTime;
        window->CurrentEventObject = nullptr;
        window->CurrentEventObjectTime = SDL_GetTicksNS();
      }
    }
  }
  return 0;
}

int handleKeyDown(SDL_Event *event, HYWindow *window) {
  if (!window->FocusObject) {
    return 0;
  }
  auto p1 = HYCombineUint32(event->key.which, event->key.scancode);
  auto p2 = HYCombineUint32(event->key.key, event->key.mod);
  // PrintDebug("code:{}",event->key.key);
  HYObjectPushEventCall(window, window->FocusObject, HYObjectEvent_KeyDown, p1, p2);
  return 0;
}

int handleKeyUp(SDL_Event *event, HYWindow *window) {
  if (!window->FocusObject) {
    return 0;
  }
  auto p1 = HYCombineUint32(event->key.which, event->key.scancode);
  auto p2 = HYCombineUint32(event->key.key, event->key.mod);
  HYObjectPushEventCall(window, window->FocusObject, HYObjectEvent_KeyUp, p1, p2);
  return 0;
}

void window_recreate_surface(HYWindow *windowPtr) {
  // 更新HDC/画笔尺寸
  if (windowPtr->Surface) {
    HYResourceRemove(ResourceType::ResourceType_Other, windowPtr->Surface);
  }

  SDL_GL_MakeCurrent(windowPtr->SDLWindow, (SDL_GLContext) windowPtr->SDLOpenGl);

  // 将附加到屏幕上的帧缓冲对象包装在Skia渲染目标中，以便Skia可以对其进行渲染
  SDL_GetWindowSizeInPixels(windowPtr->SDLWindow, &windowPtr->ClientRect.width, &windowPtr->ClientRect.height);

  glViewport(0, 0, windowPtr->ClientRect.width, windowPtr->ClientRect.height);
  GrGLint buffer;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
  GrGLFramebufferInfo binfo;
  binfo.fFBOID = (GrGLuint) buffer;
#if defined(_HOST_ANDROID_)
  binfo.fFormat = GL_RGBA8_OES;
#else
  binfo.fFormat = GL_RGBA8;
#endif
  auto grtarget = GrBackendRenderTargets::MakeGL(windowPtr->ClientRect.width,
                                                 windowPtr->ClientRect.height,
                                                 0, 8,
                                                 binfo);

  SkSurfaceProps props = {0, kUnknown_SkPixelGeometry};

  sk_sp<SkSurface> surface(SkSurfaces::WrapBackendRenderTarget(((GrDirectContext *) windowPtr->GrCtx), grtarget,
                                                               kBottomLeft_GrSurfaceOrigin,
                                                               kRGBA_8888_SkColorType, nullptr, &props));
  windowPtr->Surface = surface.release();
  if (!windowPtr->Surface) {
    // 硬件加速失败
    PrintError("Hardware acceleration failed, fallback to software rendering");
    exit(1);
  }
  HYResourceRegisterOther(windowPtr->Surface, "skia surface", [](void *ptr) {
    SkSafeUnref((SkSurface *) ptr);
  });
  windowPtr->Canvas = windowPtr->Surface->getCanvas();

  HYWindowSendEventRePaint(windowPtr);
}

void HYWindowSkinHook(HYWindow *wnd, HYRGB backGroundColor, int diaphaneity, double round) {
  //  wnd->EventQueue.SetProcessCallback(processing_object_event);
  wnd->round = round;
  wnd->BackGroundColor = HYColorRGBToInt(backGroundColor);
  wnd->Diaphaneity = diaphaneity;

  if (!wnd->CursorMap.empty()) {
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
                                                  SDL_DestroyCursor((SDL_Cursor *) resource);
                                                });
  }
  window_hook_handel(wnd);
  SDL_SetWindowOpacity(wnd->SDLWindow, (float) (diaphaneity) / 255.0f);
  window_recreate_surface(wnd);
}

uint32_t HYWindowMessageLoop() {
  g_app.isRuning = true;
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
    // std::lock_guard<std::mutex> lock_win_table(g_app.WindowsTableMutex);
    std::lock_guard<std::mutex> look_up_lock(g_app.LookupLock);
    if (!g_app.isRuning) {
      break;
    }
    frameStart = SDL_GetTicks();
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) {
      // 退出事件
      break;
    }
    if (event.window.windowID < 1) {
      //tic_fps_func();
      continue;
    }
    // std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
    auto window = HYWindowGetWindowFromID(event.window.windowID);
    if (!window) {
      continue;
    }

    if (!window->IsInit) {
      window->IsInit = true;
      if (window->Show) {
        SDL_ShowWindow(window->SDLWindow);
      }
    }
    // ---------------------窗口事件---------------------------------
    if (event.type == SDL_EventType::SDL_EVENT_WINDOW_MOVED) {
      // 窗口移动
      SDL_GetWindowPosition(window->SDLWindow, &window->X, &window->Y);
    } else if (event.type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_LEAVE) {
      // 窗口失去焦点
    } else if (event.type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_ENTER) {
      // 窗口获得焦点
    } else if (event.type == SDL_EventType::SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
      // 窗口大小/位置改变
      SDL_GetWindowSize(window->SDLWindow, &window->Width, &window->Height);
      window_recreate_surface(window);
    } else if (event.type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN) {
      // 鼠标按键按下事件
      if (handleMouseButtonDown(&event, window) != 0) {
        continue;
      }
    } else if (event.type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP) {
      // 鼠标按键抬起事件
      if (handleMouseButtonUp(&event, window) != 0) {
        continue;
      }
    } else if (event.type == SDL_EventType::SDL_EVENT_MOUSE_WHEEL) {
      // 鼠标滚轮事件
      if (handleMouseWheel(&event, window) != 0) {
        continue;
      }
    } else if (event.type == SDL_EventType::SDL_EVENT_MOUSE_MOTION) {
      // 鼠标移动事件
      if (handleMouseMotion(&event, window) != 0) {
        continue;
      }
    } else if (event.type == SDL_EventType::SDL_EVENT_KEY_DOWN) {
      // 键盘按键按下事件
      if (handleKeyDown(&event, window) != 0) {
        continue;
      }
    } else if (event.type == SDL_EventType::SDL_EVENT_KEY_UP) {
      // 键盘按键抬起事件
      if (handleKeyUp(&event, window) != 0) {
        continue;
      }
    } else if (event.type == g_app.EventWindow) {
      // 自定义窗口事件
      auto iter = g_win_event_map.find(event.window.reserved);
      if (iter != g_win_event_map.end())
        iter->second(window, &event.window);
    } else if (event.type == g_app.EventObject) {
      // 自定义组件事件
      auto ts = (uint64_t *) event.user.data1;
      auto object = (HYObjectHandle) ts;
      auto param1 = *(uint64_t *) ((uintptr_t(ts) + sizeof(uint64_t *)));
      auto param2 = *(uint64_t *) ((uintptr_t(ts) + sizeof(uint64_t *) + sizeof(uint64_t *)));
      free(ts);
      if (object) {
        _obj_event(window, object, (HYObjectEvent) event.user.code, param1, param2);
      }
    }
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

WindowHandelInfo HYWindowGetHandel(HYWindowHandel wnd) {
#if defined(_HOST_WINDOWS_)
  // HWND
  return {
    .handle = (HWND) SDL_GetPropertyType(SDL_GetWindowProperties(wnd->SDLWindow), SDL_PROP_WINDOW_WIN32_HWND_POINTER)};
#elif defined(_HOST_MACOS_)
  NSWindow *nswindow = (__bridge NSWindow *) SDL_GetPropertyType(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER);
  if (nswindow) {
    ...
  }
#elif defined(_HOST_LINUX_)
  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
    auto xdisplay = (Display *) SDL_GetPropertyType(SDL_GetWindowProperties(wnd->SDLWindow),
                                                    SDL_PROP_WINDOW_X11_DISPLAY_POINTER);
    auto xwindow = (Window) SDL_GetNumberProperty(SDL_GetWindowProperties(wnd->SDLWindow),
                                                  SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
    return {false, xdisplay, xwindow};
  } else if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
    struct wl_display *display = (struct wl_display *) SDL_GetPropertyType(SDL_GetWindowProperties(wnd->SDLWindow),
                                                                           SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER);
    struct wl_surface *surface = (struct wl_surface *) SDL_GetPropertyType(SDL_GetWindowProperties(wnd->SDLWindow),
                                                                           SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER);
    return {true, display, (uintptr_t) surface};
  }
#elif defined(SDL_PLATFORM_IOS)
  SDL_PropertiesID props = SDL_GetWindowProperties(window);
  UIWindow *uiwindow = (__bridge UIWindow *) SDL_GetProperty(props, SDL_PROP_WINDOW_UIKIT_WINDOW_POINTER, NULL);
  if (uiwindow) {
    GLuint framebuffer = (GLuint) SDL_GetNumberProperty(props, SDL_PROP_WINDOW_UIKIT_OPENGL_FRAMEBUFFER_NUMBER, 0);
    GLuint colorbuffer = (GLuint) SDL_GetNumberProperty(props, SDL_PROP_WINDOW_UIKIT_OPENGL_RENDERBUFFER_NUMBER, 0);
    GLuint resolveFramebuffer = (GLuint) SDL_GetNumberProperty(props, SDL_PROP_WINDOW_UIKIT_OPENGL_RESOLVE_FRAMEBUFFER_NUMBER, 0);
  }
  return;
#else
#error "Not support"
#endif
}

HYWindow *HYWindowGetWindowFromHandle(const WindowHandelInfo &handle) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto &debug_app = g_app;
  if (!g_app.WindowsTable.empty()) {
    for (auto &iter: g_app.WindowsTable) {
      if (iter->Handle.handle == handle.handle) {
        return iter;
      }
    }
  }
  return nullptr;
}

HYWindow *HYWindowGetWindowFromID(int id) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto &debug_app = g_app;
  if (!g_app.WindowsTable.empty()) {
    for (auto &iter: g_app.WindowsTable) {
      if (iter->ID == id) {
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
  event.window.reserved = HYWindowEvent_Paint;
  event.window.data1 = 0;
  event.window.data2 = 0;
  SDL_PushEvent(&event);
}


}// namespace HYGUI
