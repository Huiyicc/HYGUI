//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H

#ifdef _HYGUI_MODULE_

#include "include/core/SkBitmap.h"
#include "include/core/SkImage.h"
#include "include/core/SkData.h"
#include <core/SkSurface.h>


#else

#define SkImage void
#define SkSurface void

#endif

#include <cstdint>
#include <set>
#include <unordered_map>
#include "String.h"

namespace HYGUI {

enum class HYGlobalFlag : uint32_t {
  HYGlobalFlagGraphicGL,

  HYGlobalFlagGraphicDefault = HYGlobalFlagGraphicGL,
};
struct HYWindow;

typedef void *VOIDPTR;
typedef intptr_t VOIDPTRT;
typedef VOIDPTR WINDOWHANDEL;
typedef SkImage *ImagePtr;
typedef SkSurface *SurfacePtr;
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
  std::set<HYWindow*> WindowsTable;
};

}


#endif //HYGUI_DEFINE_H
