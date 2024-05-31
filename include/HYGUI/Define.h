//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H

#ifdef _HYGUI_MODULE_
#include "include/core/SkBitmap.h"
#include "include/core/SkImage.h"
#include "include/core/SkData.h"

#else

#define SkImage void

#endif

#include <cstdint>
#include "String.h"

namespace HYGUI {

typedef void *VOIDPTR;
typedef SkImage* ImagePtr;
typedef VOIDPTR CursorPtr;


struct ApplicationInfo {
  HYString LastError;
  VOIDPTR Instance = nullptr;
  uint32_t GlobalFlags = 0;
  HYString DefaultClassName;
  CursorPtr Cursor = nullptr;
  VOIDPTR Icon = nullptr;
  VOIDPTR IconSm = nullptr;
};

}



#endif //HYGUI_DEFINE_H
