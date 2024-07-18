//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_TYPEDEF_H
#define HYGUI_TYPEDEF_H

#ifdef _HYGUI_MODULE_

#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkData.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkImage.h"
#include "include/core/SkPaint.h"
#include "include/core/SkSurface.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkRefCnt.h"
class SkShader;

#else

#define SkImage void
#define SkSurface void
#define SkCanvas void
#define SkPaint void
#define SkTypeface void
#define SkFont void
#define SkFontMgr void
#define SkTextBlobBuilder void
#define SkShader void


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
 * @brief 字体族指针
 * */
typedef SkTypeface *TypefacePtr;
/**
 * @brief 字体指针
 * */
typedef SkFont *FontPtr;
/**
 * @brief 字体管理器指针
 * */
typedef SkFontMgr *FontMgrPtr;
/**
 * @brief 文本块构建器指针
 * */
typedef SkTextBlobBuilder *TextBlobBuilderPtr;
/**
 * @brief 着色器指针
 * */
typedef SkShader *ShaderPtr;

}



#endif//HYGUI_TYPEDEF_H
