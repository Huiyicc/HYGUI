//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H
#include <cstdint>
#include <set>
#include <unordered_map>
#include "String.h"
#include <mutex>

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

enum class HYGlobalFlag : uint32_t {
  HYGlobalFlagGraphicNone = 0,
  // HYGlobalFlagGraphicGL,

  HYGlobalFlagGraphicDefault = HYGlobalFlagGraphicNone,
};

struct HYWindow;

typedef void *VOIDPTR;
typedef intptr_t VOIDPTRT;
typedef VOIDPTR WINDOWHANDEL;
typedef VOIDPTR CursorPtr;


struct ApplicationInfo {
  HYString LastError;
  int kStencilBits;
  VOIDPTR Instance = nullptr;
  VOIDPTR GrContext = nullptr;
  HYGlobalFlag GlobalFlags = HYGlobalFlag::HYGlobalFlagGraphicDefault;
  HYString DefaultClassName;
  CursorPtr Cursor = nullptr;
  VOIDPTR Icon = nullptr;
  VOIDPTR IconSm = nullptr;
  std::set<HYWindow *> WindowsTable;
  std::mutex WindowsTableMutex;
  uint32_t EventCustomStart;
  uint32_t EventWindow;
  uint32_t EventObject;
};



}
#include "Draw.h"
#include "Cursor.h"
#include "Point.h"

#endif //HYGUI_DEFINE_H
