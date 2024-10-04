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

#include <HYGUI/HYContext.h>
#include <HYGUI/HYWindow.h>
#include <gpu/ganesh/SkSurfaceGanesh.h>

namespace HYGUI {

HYWindow::HYWindow() {
std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
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
                                     //                                     | SDL_WINDOW_HIDDEN       // 隐藏
                                     | SDL_WINDOW_RESIZABLE // 可调整大小
                                     | SDL_WINDOW_BORDERLESS// 无边框
                                     | SDL_WINDOW_TRANSPARENT);
  if (sdl_wind == nullptr) {
    THROW_ERROR("创建窗口失败");
  }

  SDL_HideWindow(sdl_wind);
  // HYResourceRegister(ResourceType::ResourceType_Window, sdl_wind, "sdl window", [](void *resource) {
  //   std::lock_guard<std::mutex> look_up_lock(g_app.LookupLock);
  //   SDL_DestroyWindow((SDL_Window *) resource);
  // });

  // 创建OpenGL上下文
  SDL_GLContext glContext = SDL_GL_CreateContext(sdl_wind);
  if (glContext == nullptr) {
    // HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    SDL_DestroyWindow(sdl_wind);
    THROW_ERROR("创建OpenGL Context失败");
  }
  // HYResourceRegisterOther(glContext, "SDL_GLContext", [](void *resource) {
  //   SDL_GL_DestroyContext((SDL_GLContext) resource);
  // });
  // 切换到OpenGL上下文
  int success = SDL_GL_MakeCurrent(sdl_wind, glContext);
  if (success != 0) {
    // HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    // HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("切换OpenGL Context失败");
  }
  // auto opengl_buffer = SDL_GetProperty(SDL_GetWindowProperties(sdl_wind), SDL_PROP_WINDOW_UIKIT_OPENGL_FRAMEBUFFER_NUMBER, nullptr);
  // glEnable(GL_MULTISAMPLE);
  static const int kMsaaSampleCount = 0;//4;

  int contextType;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextType);
  int dw, dh;
  SDL_GetWindowSizeInPixels(sdl_wind, &dw, &dh);
  glViewport(0, 0, dw, dh);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // // 准备GrContext
  // auto skInterface = GrGLMakeNativeInterface();
  // if (!skInterface) {
  //   skInterface = GrGLMakeAssembledInterface(
  //     nullptr, glgetpoc);
  // }
  //
  // if (!skInterface) {
  //   // HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
  //   // HYResourceRemove(ResourceType::ResourceType_Other, glContext);
  //   SDL_DestroyWindow(sdl_wind);
  //   SDL_GL_DestroyContext(glContext);
  //   THROW_ERROR("创建Native Interface失败");
  // }
  // // 准备contexts
  // sk_sp<GrDirectContext> grContext(GrDirectContexts::MakeGL(skInterface));
  m_GrCtx = HYGrDirectContext::MakeFromDefaultInterface();
  if (!m_GrCtx) {
    // HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    // HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("创建Direct Context失败");
  }

  // auto grctx = grContext.release();
  // GrCtx = HYResourceRegisterOther(grctx, "GrDirectContext", [](void *resource) {
  //   auto ctx = (GrDirectContext *) resource;
  //   ctx->abandonContext();
  //   SkSafeUnref(ctx);
  // });
  //window->GrCtx = HYResourceRegisterOther(grctx, "GrDirectContext", nullptr);
  m_SDLOpenGl = glContext;
  m_ID = SDL_GetWindowID(sdl_wind);
  m_SDLWindow = sdl_wind;
  m_ClientRect = {0, 0, dw, dh};

  auto hWnd = GetHandel();
  if (hWnd.handle == nullptr) {
    g_app.LastError = "Create window fail";
    // HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    // HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    // HYResourceRemove(ResourceType::ResourceType_Other, GrCtx);
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("创建窗口失败");
  }
  SDL_GetWindowPosition(sdl_wind, &m_x, &m_y);
  SDL_GetWindowSize(sdl_wind, &m_width, &m_height);
  m_ClientRect = {0, 0, m_width, m_height};

  if (g_app.WindowsTable.find(this) != g_app.WindowsTable.end()) {
    // ????什么玩意
    // HYResourceRemove(ResourceType::ResourceType_Window, sdl_wind);
    // HYResourceRemove(ResourceType::ResourceType_Other, glContext);
    // HYResourceRemove(ResourceType::ResourceType_Other, GrCtx);
    SDL_DestroyWindow(sdl_wind);
    SDL_GL_DestroyContext(glContext);
    THROW_ERROR("申请窗口资源冲突");
  }
  g_app.WindowsTable.insert(this);
  // HYResourceRegister(ResourceType::ResourceType_Window, this, "hywindow", [](void *resource) {
  //   delete (HYWindow *) resource;
  // });
  // HYResourceRemoveClearFunc(ResourceType::ResourceType_Window, sdl_wind);
  // HYWindowSendEvent(this, HYWindowEvent::HYWindowEvent_Create, 0, 0);

}

HYWindow::~HYWindow() {

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

