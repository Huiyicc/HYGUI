//
// Created by 回忆 on 24-6-10.
//
#include "HYGUI/Image.h"
#include "PrivateDefinition.h"
#include <ApplicationServices/ApplicationServices.h>
#ifdef _HOST_APPLE_
#include <Cocoa/Cocoa.h>
#endif

namespace HYGUI {

CursorPtr HYCursorLoadFromDefault() {
  if (g_app.Cursor) {
    return g_app.Cursor;
  }
  g_app.Cursor = [NSCursor arrowCursor];
  return g_app.Cursor;
}

CursorPtr HYCursorLoadFromImage(ImagePtr image) {
  // 获取图像宽高
  int width = image->width();
  int height = image->height();

  // 保证图像为ARGB格式，获取图像像素数据
  SkPixmap pixmap;
  if (!image->peekPixels(&pixmap)) {
    // 处理获取像素数据失败的情况
    std::cerr << "获取图像像素数据失败" << std::endl;
    return nullptr;
  }

  // 确保像素格式正确处理
  if (pixmap.colorType() != kRGBA_8888_SkColorType) {
    // 处理像素格式错误的情况
    std::cerr << "图像像素格式错误" << std::endl;
    return nullptr;
  }

  // 创建CGImageRef
  CGDataProviderRef dataProvider = CGDataProviderCreateWithData(nullptr, pixmap.addr(), pixmap.computeByteSize(), nullptr);
  CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
  CGImageRef cgImage = CGImageCreate(width, height, 8, 32, pixmap.rowBytes(), colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big, dataProvider, nullptr, false, kCGRenderingIntentDefault);
  CGColorSpaceRelease(colorSpace);
  CGDataProviderRelease(dataProvider);

  if (!cgImage) {
    std::cerr << "创建CGImage失败" << std::endl;
    return nullptr;
  }

  // 创建NSImage
  NSImage* nsImage = [[NSImage alloc] initWithCGImage:cgImage size:NSMakeSize(width, height)];
  CGImageRelease(cgImage);

  if (!nsImage) {
    std::cerr << "创建NSImage失败" << std::endl;
    return nullptr;
  }

  // 创建NSCursor
  NSCursor* cursor = [[NSCursor alloc] initWithImage:nsImage hotSpot:NSMakePoint(0, 0)];
  [nsImage release];

  if (!cursor) {
    std::cerr << "创建光标失败" << std::endl;
    return nullptr;
  }

  return cursor;
}

}