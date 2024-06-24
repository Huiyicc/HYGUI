//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_DRAW_H
#define HYGUI_DRAW_H

#ifdef _HYGUI_MODULE_

#include "include/core/SkBitmap.h"
#include "include/core/SkImage.h"
#include "include/core/SkData.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkFont.h"
#include <core/SkSurface.h>

#else

#define SkImage void
#define SkSurface void
#define SkCanvas void
#define SkPaint void
#define SkTypeface void
#define SkFont void

#endif

namespace HYGUI {

/**
 * @brief 图像指针
 * */
typedef SkImage *ImagePtr;
/**
 * @brief 纹理指针
 * */
typedef SkSurface *SurfacePtr;
/**
 * @brief 画布指针
 * */
typedef SkCanvas *CanvasPtr;
/**
 * @brief 画笔指针
 * */
typedef SkPaint *PaintPtr;
/**
 * @brief 字体风格指针
 * */
typedef SkTypeface *TypefacePtr;
/**
 * @brief 字体指针
 * */
typedef SkFont *FontPtr;

}



#endif //HYGUI_DRAW_H
