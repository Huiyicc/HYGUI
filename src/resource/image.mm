//
// Created by 回忆 on 24-6-17.
//
#include "HYGUI/Image.h"
#include "PrivateDefinition.h"
#import <Cocoa/Cocoa.h>

namespace HYGUI {


CursorPtr HYCursorLoadFromDefault() {
  NSCursor *defaultCursor = [NSCursor arrowCursor];
  return reinterpret_cast<CursorPtr>(defaultCursor);
}

NSImage* SkImageToNSImage(ImagePtr skImage) {
  // 获取SkImage的信息
  SkPixmap pixmap;
  if (!skImage->peekPixels(&pixmap)) {
    return nil;
  }

  // 创建NSBitmapImageRep
  NSBitmapImageRep* imageRep = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:NULL
                                                                       pixelsWide:pixmap.width()
                                                                       pixelsHigh:pixmap.height()
                                                                    bitsPerSample:8
                                                                  samplesPerPixel:4
                                                                         hasAlpha:YES
                                                                         isPlanar:NO
                                                                   colorSpaceName:NSDeviceRGBColorSpace
                                                                      bytesPerRow:pixmap.rowBytes()
                                                                     bitsPerPixel:32];

  // 将SkImage的数据拷贝到NSBitmapImageRep
  memcpy([imageRep bitmapData], pixmap.addr(), pixmap.computeByteSize());

  // 创建NSImage并添加NSBitmapImageRep
  NSImage* nsImage = [[NSImage alloc] initWithSize:NSMakeSize(pixmap.width(), pixmap.height())];
  [nsImage addRepresentation:imageRep];

  // 释放NSBitmapImageRep
  [imageRep release];

  return nsImage;
}


CursorPtr HYCursorLoadFromImage(ImagePtr image) {
  NSImage *nsImage = SkImageToNSImage(image);
  if (!nsImage) {
    g_app.LastError = "无法将图像转换为Mac兼容格式";
    return nullptr;
  }

  // 设置热区，默认为图像中心，根据需求调整
  NSPoint hotSpot = NSMakePoint(nsImage.size.width / 2, nsImage.size.height / 2);

  // 创建并返回自定义光标
  NSCursor *customCursor = [[NSCursor alloc] initWithImage:nsImage hotSpot:hotSpot];
  return reinterpret_cast<CursorPtr>(customCursor);
}

}