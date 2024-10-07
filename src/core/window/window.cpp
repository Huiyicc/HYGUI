//
// Created by 回忆 on 24-10-4.
//
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
#elif defined(_HOST_APPLE_)

#endif

#include "SDL3/SDL.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/gl/GrGLTypes.h"

#include <HYGUI/HYColor.h>
#include <HYGUI/HYContext.h>
#include <HYGUI/HYCursor.h>
#include <HYGUI/HYWindow.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>

namespace HYGUI {

HYWindow::HYWindow() : m_Surface(nullptr) {
  m_paintMutex = std::make_shared<std::mutex>();
  m_messageMutex = std::make_shared<std::mutex>();
  m_paintCV = std::make_shared<std::condition_variable>();
  auto dsinfo = SDL_GetDesktopDisplayMode(1);
  if (m_x == WINDOWCREATEPOINT_USEDEFAULT) {
    m_x = (dsinfo->w - m_width) / 2;
  }
  if (m_y == WINDOWCREATEPOINT_USEDEFAULT) {
    m_y = (dsinfo->h - m_height) / 2;
  }
  auto sdl_wind = SDL_CreateWindow(m_title.toStdString().c_str(), m_width, m_height,
                                   SDL_WINDOW_OPENGL                // opengl
                                     | SDL_WINDOW_HIGH_PIXEL_DENSITY// 高dpi
                                     | SDL_WINDOW_HIDDEN       // 隐藏
                                     | SDL_WINDOW_RESIZABLE // 可调整大小
                                     | SDL_WINDOW_BORDERLESS// 无边框
                                     | SDL_WINDOW_TRANSPARENT);
  if (sdl_wind == nullptr) {
    THROW_ERROR("创建窗口失败");
  }

  // SDL_HideWindow(sdl_wind);

  // 创建OpenGL上下文
  SDL_GLContext glContext = SDL_GL_CreateContext(sdl_wind);
  if (glContext == nullptr) {
    SDL_DestroyWindow(sdl_wind);
    THROW_ERROR("创建OpenGL Context失败");
  }
  // 切换到OpenGL上下文
  auto success = SDL_GL_MakeCurrent(sdl_wind, glContext);
  if (!success) {
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("切换OpenGL Context失败");
  }
  int contextType;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextType);
  int dw, dh;
  SDL_GetWindowSizeInPixels(sdl_wind, &dw, &dh);
  glViewport(0, 0, dw, dh);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // 准备contexts
  m_GrCtx = HYGrDirectContext::MakeFromDefaultInterface();
  if (!m_GrCtx) {
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("创建Direct Context失败");
  }

  m_SDLOpenGl = glContext;
  m_id = SDL_GetWindowID(sdl_wind);
  m_SDLWindow = sdl_wind;
  m_ClientRect = {0, 0, dw, dh};

  auto hWnd = GetHandel();
  if (hWnd.handle == nullptr) {
    g_app.LastError = "Create window fail";
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("创建窗口失败");
  }
  SDL_GetWindowPosition(sdl_wind, &m_x, &m_y);
  SDL_GetWindowSize(sdl_wind, &m_width, &m_height);
  m_ClientRect = {0, 0, m_width, m_height};
  bool oops = false;
  for (auto &iter: g_app.WindowsTable) {
    if (iter.get() == this) {
      oops = true;
    }
  }
  if (oops) {
    // ????什么玩意
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("申请窗口资源冲突");
  }
  skinHook();
  HYWindowSendEvent(this, HYWindowEvent::HYWindowEvent_Create, 0, 0);
}

HYWindow::~HYWindow() {
  SDL_DestroyWindow(m_SDLWindow);
  SDL_GL_DestroyContext(m_SDLOpenGl);
}

void HYWindow::Show() {
  m_show = true;
  if (m_isInit) {
    SDL_ShowWindow(m_SDLWindow);
  } else {
    HYWindowSendEvent(this, HYWindowEvent::HYWindowEvent_Show, 0, 0);
  }
}

uint32_t HYWindow::ID() const {
  return m_id;
};


void HYWindow::Refresh() const {
  // 切换到OpenGL上下文
  SDL_GL_MakeCurrent(m_SDLWindow, m_SDLOpenGl);

  auto canvas = m_Surface->getCanvas();
  // 透明背景
  if (round > 0) {
    // 圆角
    SkRRect roundRect;
    roundRect.setRectXY(SkRect::MakeXYWH(0, 0, m_width, m_height),
                        round, round);
    canvas->clipRRect(roundRect);
  }


  SkPaint bgpaint;
  // bgpaint.setColor(HYColorRGBToARGBInt(m_backGroundColor, 255));
  bgpaint.setColor(HYColorARGBToInt({255, 255, 255, 255}));
  // 白色
  bgpaint.setAntiAlias(true);
  canvas->drawRect(SkRect::MakeLTRB(0, 0, m_ClientRect.width, m_ClientRect.height),
                   bgpaint);
  HYRect bgpaint_rect = {0, 0, m_width, m_height};
  // for (auto &reiter: EventBackgroundPaintCallbacks) {
  //   reiter.second(this, canvas, &bgpaint, &bgpaint_rect);
  // }

  // 子组件绘制
  canvas->save();
  // for (auto obj: Children) {
  //   // 子组件绘制
  //   HYObjectPushEventCall(this, obj, HYObjectEvent::HYObjectEvent_Paint, 0, 1);
  // }

  canvas->restore();
  canvas->resetMatrix();

  m_GrCtx->flush(m_Surface.get());

  // 将绘制的内容显示到窗口
  SDL_GL_SwapWindow(m_SDLWindow);
};

void HYWindow::skinHook() {
  m_cursorMap.clear();
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
    m_cursorMap[cursor] = HYCursor::MakeFromSystemCursor(cursor);
  }
  window_hook_handel(this);
  SDL_SetWindowOpacity(m_SDLWindow, static_cast<float>(m_diaphaneity) / 255.0f);
  recreate_surface();
}

void HYWindow::recreate_surface() {
  // 更新HDC/画笔尺寸
  if (m_Surface) {
    // HYResourceRemove(ResourceType::ResourceType_Other, m_Surface);
  }

  SDL_GL_MakeCurrent(m_SDLWindow, (SDL_GLContext) m_SDLOpenGl);

  // 将附加到屏幕上的帧缓冲对象包装在Skia渲染目标中，以便Skia可以对其进行渲染
  SDL_GetWindowSizeInPixels(m_SDLWindow, &m_ClientRect.width, &m_ClientRect.height);

  glViewport(0, 0, m_ClientRect.width, m_ClientRect.height);
  GrGLint buffer;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);
  GrGLFramebufferInfo binfo;
  binfo.fFBOID = (GrGLuint) buffer;
#if defined(_HOST_ANDROID_)
  binfo.fFormat = GL_RGBA8_OES;
#else
  binfo.fFormat = GL_RGBA8;
#endif
  auto grtarget = GrBackendRenderTargets::MakeGL(m_ClientRect.width,
                                                 m_ClientRect.height,
                                                 0, 8,
                                                 binfo);

  SkSurfaceProps props = {0, kUnknown_SkPixelGeometry};

  sk_sp<SkSurface> surface(SkSurfaces::WrapBackendRenderTarget((m_GrCtx.get()), grtarget,
                                                               kBottomLeft_GrSurfaceOrigin,
                                                               kRGBA_8888_SkColorType, nullptr, &props));
  m_Surface = HYSurface(surface.release());
  if (!m_Surface) {
    // 硬件加速失败
    PrintError("Hardware acceleration failed, fallback to software rendering");
    exit(1);
  }
  // HYResourceRegisterOther(m_Surface, "skia surface", [](void *ptr) {
  //   SkSafeUnref((SkSurface *) ptr);
  // });
  m_Canvas = m_Surface->getCanvas();

  // HYWindowSendEventRePaint(this);
}

#if !defined(_HOST_APPLE_)
WindowHandelInfo HYWindow::GetHandel() const {
#if defined(_HOST_WINDOWS_)
  // HWND
  return {
    .handle = (HWND) SDL_GetPropertyType(SDL_GetWindowProperties(m_SDLWindow), SDL_PROP_WINDOW_WIN32_HWND_POINTER)};
// #elif defined(_HOST_APPLE_)
//   NSWindow *nswindow = (__bridge NSWindow *) SDL_GetPropertyType(SDL_GetWindowProperties(m_SDLWindow), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER);
//   if (nswindow) {
//     ...
//   }
#elif defined(_HOST_LINUX_)
  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
    auto xdisplay = (Display *) SDL_GetPropertyType(SDL_GetWindowProperties(wnd->SDLWindow),
                                                    SDL_PROP_WINDOW_X11_DISPLAY_POINTER);
    auto xwindow = (Window) SDL_GetNumberProperty(SDL_GetWindowProperties(SDLWindow),
                                                  SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
    return {false, xdisplay, xwindow};
  } else if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
    struct wl_display *display = (struct wl_display *) SDL_GetPropertyType(SDL_GetWindowProperties(SDLWindow),
                                                                           SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER);
    struct wl_surface *surface = (struct wl_surface *) SDL_GetPropertyType(SDL_GetWindowProperties(SDLWindow),
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
#endif


};

