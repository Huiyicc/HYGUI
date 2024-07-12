//
// Created by 19254 on 24-5-31.
//

#include <SDL3/SDL_system.h>

#include "HYGUI/Image.h"
#include "PrivateDefinition.h"
#ifdef _HOST_LINUX_

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>

#endif


namespace HYGUI {
ImagePtr HYImageLoadFromFile(const HYString &path) {
  sk_sp<SkData> data = SkData::MakeFromFileName(path.toStdStringView().data());
  if (!data) {
    g_app.LastError = std::format("加载图片失败: MakeFromFileName(\"{}\")", path.toStdStringView());
    return nullptr;
  }
  auto image = SkImages::DeferredFromEncodedData(data);
  if (!image) {
    g_app.LastError = std::format("加载图片失败: DeferredFromEncodedData(\"{}\")", path.toStdStringView());
    return nullptr;
  }
  return image.release();
};

void HYImageRelease(ImagePtr image) {
  SkSafeUnref(image);
}
#ifdef _HOST_WINDOWS_
CursorPtr HYCursorLoadFromDefault() {
  if (g_app.Cursor) {
    return g_app.Cursor;
  }

  return LoadCursorW(nullptr, reinterpret_cast<LPCWSTR>(IDC_ARROW));
}



CursorPtr HYCursorLoadFromImage(HYWindow*wnd,ImagePtr image) {
  // 加载光标
  int width = image->width();
  int height = image->height();
  // 保证图像为ARGB格式，获取图像像素数据
  SkPixmap pixmap;
  if (!image->peekPixels(&pixmap)) {
    g_app.LastError = "获取图像像素数据失败";
    return nullptr;
  }
  // 确保像素格式正确处理
  if (pixmap.colorType() != kRGBA_8888_SkColorType) {
    g_app.LastError = "图像像素格式错误";
    return nullptr;
  }
  // 创建光标
  ICONINFO iconInfo;
  iconInfo.fIcon = FALSE;
  iconInfo.xHotspot = 0;
  iconInfo.yHotspot = 0;
  iconInfo.hbmMask = CreateBitmap(width, height, 1, 1, nullptr);
  if (!iconInfo.hbmMask) {
    g_app.LastError = "创建光标掩码失败";
    return nullptr;
  }
  iconInfo.hbmColor = CreateBitmap(width, height, 1, 32, pixmap.writable_addr());
  if (!iconInfo.hbmColor) {
    g_app.LastError = "创建光标颜色位图失败";
    return nullptr;
  }
  // 创建光标
  auto cursor = CreateIconIndirect(&iconInfo);
  if (!cursor) {
    g_app.LastError = "创建光标失败";
    return nullptr;
  }
  return cursor;

};
#elif defined(_HOST_APPLE_)
#elif defined(_HOST_LINUX_)
CursorPtr HYCursorLoadFromDefault(HYWindow*wnd,HYWindow *wind) {
  if (g_app.Cursor) {
    return g_app.Cursor;
  }
  SDL_SysWMinfo info;
  SDL_GetWindowWMInfo(wind->SDLWindow, &info);
  // 创建一个默认光标（箭头光标）
  return (CursorPtr) XCreateFontCursor(info.info.x11.display, XC_left_ptr);
}

CursorPtr HYCursorLoadFromImage(HYWindow *wind, ImagePtr image) {
  // 加载光标
  int width = image->width();
  int height = image->height();

  // 保证图像为ARGB格式，获取图像像素数据
  SkPixmap pixmap;
  if (!image->peekPixels(&pixmap)) {
    g_app.LastError = "获取图像像素数据失败";
    return 0;
  }

  // 确保像素格式正确处理
  if (pixmap.colorType() != kRGBA_8888_SkColorType) {
    g_app.LastError = "图像像素格式错误";
    return 0;
  }
  SDL_SysWMinfo info;
  SDL_GetWindowWMInfo(wind->SDLWindow, &info);
  auto &display = info.info.x11.display;
  auto &rootWindow = info.info.x11.window;
  // 创建一个位图掩码（全透明）
  Pixmap maskPixmap = XCreatePixmap(display, rootWindow, width, height, 1);
  GC gc = XCreateGC(display, maskPixmap, 0, NULL);
  XSetForeground(display, gc, 0);
  XFillRectangle(display, maskPixmap, gc, 0, 0, width, height);
  XFreeGC(display, gc);

  // 创建颜色位图
  Pixmap colorPixmap = XCreatePixmap(display, rootWindow, width, height, 32);
  gc = XCreateGC(display, colorPixmap, 0, NULL);

  // 复制图像像素到颜色位图
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      SkColor color = pixmap.getColor(x, y);
      XSetForeground(display, gc, (color & 0xFFFFFFFF));
      XDrawPoint(display, colorPixmap, gc, x, y);
    }
  }

  XFreeGC(display, gc);

  // 创建光标
  XColor dummyColor;
  Cursor cursor = XCreatePixmapCursor(display, colorPixmap, maskPixmap, &dummyColor, &dummyColor, 0, 0);

  // 释放位图
  XFreePixmap(display, colorPixmap);
  XFreePixmap(display, maskPixmap);

  if (!cursor) {
    g_app.LastError = "创建光标失败";
    return 0;
  }

  return (CursorPtr) cursor;
}
#else
#error "Unsupported platform"
#endif

CursorPtr HYCursorLoadFromFile(HYWindow*wnd,HYWindow *wind, const HYString &path) {
  auto image = HYImageLoadFromFile(path);
  if (!image) {
    return nullptr;
  }
  auto cursor = HYCursorLoadFromImage(wind, image);
  HYImageRelease(image);
  if (!cursor) {
    return nullptr;
  }
  return cursor;
}
}
