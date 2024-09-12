//
// Created by 19254 on 24-5-31.
//
#define GLFW_INCLUDE_NONE

#include "HYGUI/Application.h"
#include "HYGUI/Define.h"
#include "PrivateDefinition.h"
#include "include/core/SkStream.h"
#include "include/core/SkTypeface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/ports/SkFontMgr_directory.h"
#include <filesystem>
#include <ports/SkTypeface_win.h>
//#include "include/gpu/gl/GrGLInterface.h"

#ifdef _HOST_WINDOWS_

//#include <gl/GL.h>
#elif defined(_HOST_APPLE_)
#include "SDL2/SDL_opengl.h"
#include "include/gpu/gl/GrGLInterface.h"
#elif defined(_HOST_LINUX_)
#include "include/ports/SkFontConfigInterface.h"
#include "include/ports/SkFontMgr_FontConfigInterface.h"
#endif

//#include <GLFW/glfw3.h>
#include "SDL3/SDL.h"
#include "emoji_font_resource.h"
#include "utils_font_resource.h"

namespace HYGUI {

ApplicationInfo g_app;

bool HYInit(HYGlobalFlag DefaultGlobalFlags,
            const HYString &DefaultFont) {
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0) {
    g_app.LastError = SDL_GetError();
    PrintError("{}",g_app.LastError.c_str());

    return false;
  };
  HYString DefaultClassName = DEFAULT_CLASS_NAME;
  // 初始化sdl gl
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#if defined(_HOST_APPLE_)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
#if defined(_HOST_ANDROID_) || defined(_HOST_IOS_)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP |
                SDL_WINDOW_ALLOW_HIGHDPI;
#else
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
  //SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

//  g_app.kStencilBits = 8;// skia需要8位模板缓冲区
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  g_app.GlobalFlags = DefaultGlobalFlags;

  // 注册sdl事件
  g_app.EventCustomStart = SDL_RegisterEvents(2);
  if (g_app.EventCustomStart == (Uint32) -1) {
    g_app.LastError = SDL_GetError();
    PrintError("{}",g_app.LastError.c_str());
    return false;
  }
  g_app.EventWindow = g_app.EventCustomStart;
  g_app.EventObject = g_app.EventCustomStart + 1;

  // 加载字体
#if defined(_HOST_WINDOWS_)
  auto mgr = SkFontMgr_New_DirectWrite();
#elif defined(_HOST_LINUX_)
  sk_sp<SkFontConfigInterface> fci(SkFontConfigInterface::RefGlobal());
  auto mgr = fci ? SkFontMgr_New_FCI(std::move(fci)) : nullptr;
#elif defined(_HOST_MACOS_)
  auto mgr = SkFontMgr_New_CoreText(nullptr);
#else
  // SkFontMgr_New_Custom_Empty()
#error "Unsupported platform"
#endif
  g_app.FontMgr = (SkFontMgr *) HYResourceRegisterOther(mgr.release(), "skfontmgr", [](void *ptr) {
    SkSafeUnref((SkFontMgr *) ptr);
  });
  if (!g_app.FontMgr) {
    PrintError("Failed to create font manager");
    g_app.LastError = "Failed to create font manager";
    return false;
  }
  bool useDefault = true;
  // 加载默认字体
  if (!DefaultFont.empty()) {
    // 设置默认字体
    std::filesystem::path fontpath(DefaultFont.toStdStringView());
    if (std::filesystem::exists(fontpath)) {
      // 文件存在
      g_app.DefaultTypeface = (SkTypeface *) HYResourceRegister(ResourceType::ResourceType_Typeface,
                                                                g_app.FontMgr->makeFromFile(DefaultFont.toStdStringView().data()).release(), "", [](void *ptr) {
                                                                  SkSafeUnref((SkTypeface *) ptr);
                                                                });
      useDefault = (g_app.DefaultTypeface == nullptr);
    }
  }
  if (useDefault) {
#ifdef _HOST_WINDOWS_
    // 微软雅黑
    g_app.DefaultTypeface = (SkTypeface *) HYResourceRegister(ResourceType::ResourceType_Typeface,
                                                              g_app.FontMgr->legacyMakeTypeface("Microsoft YaHei", SkFontStyle()).release(), "", [](void *ptr) {
                                                                SkSafeUnref((SkTypeface *) ptr);
                                                              });
#else
    g_app.DefaultTypeface = (SkTypeface *) HYResourceRegister(ResourceType::ResourceType_Typeface,
                                                              g_app.FontMgr->legacyMakeTypeface("FangSong", SkFontStyle()).release(), "", [](void *ptr) {
                                                                SkSafeUnref((SkTypeface *) ptr);
                                                              });
#endif
  }
  {
    auto emojiStream = SkMemoryStream::MakeDirect(emoji_font_resource,emoji_font_resource_len);
    std::unique_ptr<SkStreamAsset> streamAsset(emojiStream.release());
    g_app.EmojiTypeface =(SkTypeface *) HYResourceRegister(ResourceType::ResourceType_Typeface,
                                      g_app.FontMgr->makeFromStream(std::move(streamAsset)).release(), "Global emoji font", [](void *ptr) {
                                        SkSafeUnref((SkTypeface *) ptr);
                                      });

  }
  {
    auto utilsStream = SkMemoryStream::MakeDirect(utils_font_resource,utils_font_resource_len);
    std::unique_ptr<SkStreamAsset> streamAsset(utilsStream.release());
    g_app.UtilsTypeface =(SkTypeface *) HYResourceRegister(ResourceType::ResourceType_Typeface,
                                                            g_app.FontMgr->makeFromStream(std::move(streamAsset)).release(), "Global utils font", [](void *ptr) {
                                                              SkSafeUnref((SkTypeface *) ptr);
                                                            });

  }

  g_app.Cursor = nullptr;
#ifdef _HOST_WINDOWS_
  //HYWindowRegisterClass(DefaultClassName);
  g_app.DefaultClassName = DefaultClassName;

// 窗口阴影
//HYWindowRegisterClass(L"SysShadow");
#endif
  return true;
}

void HYExit() {

  std::lock_guard<std::mutex> look_up_lock(g_app.LookupLock);

  g_app.isRuning = false;
  SDL_Quit();
  HYResourceRemoveOther(g_app.FontMgr);
  // debug

  HYResourceDumpDebug();

}


}// namespace HYGUI