//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H

#ifdef _HYGUI_MODULE_

#include "include/core/SkBitmap.h"
#include "include/core/SkImage.h"
#include "include/core/SkData.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include <core/SkSurface.h>


#else

#define SkImage void
#define SkSurface void
#define SkCanvas void
#define SkPaint void

#endif

#include <cstdint>
#include <set>
#include <unordered_map>
#include "String.h"

namespace HYGUI {

enum class HYGlobalFlag : uint32_t {
  HYGlobalFlagGraphicNone = 0,
  // HYGlobalFlagGraphicGL,

  HYGlobalFlagGraphicDefault = HYGlobalFlagGraphicNone,
};

struct HYWindow;

typedef void *VOIDPTR;
typedef intptr_t VOIDPTRT;
typedef VOIDPTR WINDOWHANDEL;
typedef SkImage *ImagePtr;
typedef SkSurface *SurfacePtr;
typedef SkCanvas *CanvasPtr;
typedef SkPaint *PaintPtr;
typedef VOIDPTR CursorPtr;


struct ApplicationInfo {
  HYString LastError;
  VOIDPTR Instance = nullptr;
  VOIDPTR GrContext = nullptr;
  HYGlobalFlag GlobalFlags = HYGlobalFlag::HYGlobalFlagGraphicDefault;
  HYString DefaultClassName;
  CursorPtr Cursor = nullptr;
  VOIDPTR Icon = nullptr;
  VOIDPTR IconSm = nullptr;
  std::set<HYWindow *> WindowsTable;
};

struct HYRect {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

}


#endif //HYGUI_DEFINE_H
