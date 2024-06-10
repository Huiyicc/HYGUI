//
// Created by 19254 on 24-5-31.
//

#include "HYGUI/Image.h"
#include "PrivateDefinition.h"



namespace HYGUI {


ImagePtr HYImageLoadFromFile(const HYString &path) {
  sk_sp<SkData> data = SkData::MakeFromFileName(path.toStdStringView().data());
  if (!data) {
    g_app.LastError = fmt::format("加载图片失败: MakeFromFileName(\"{}\")", path.toStdStringView());
    return nullptr;
  }
  auto image = SkImages::DeferredFromEncodedData(data);
  if (!image) {
    g_app.LastError = fmt::format("加载图片失败: DeferredFromEncodedData(\"{}\")", path.toStdStringView());
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



CursorPtr HYCursorLoadFromImage(ImagePtr image) {
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
#else
#error "Unsupported platform"
#endif

CursorPtr HYCursorLoadFromFile(const HYString &path) {
  auto image = HYImageLoadFromFile(path);
  if (!image) {
    return nullptr;
  }
  auto cursor = HYCursorLoadFromImage(image);
  HYImageRelease(image);
  if (!cursor) {
    return nullptr;
  }
  return cursor;
}

}