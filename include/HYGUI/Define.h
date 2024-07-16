//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H
#include "String.h"
#include "TypeDef.h"
#include <cstdint>
#include <mutex>
#include <set>
#include <unordered_map>

namespace HYGUI {

enum class HYGlobalFlag : uint32_t {
  HYGlobalFlagGraphicNone = 0,
  // HYGlobalFlagGraphicGL,

  HYGlobalFlagGraphicDefault = HYGlobalFlagGraphicNone,
};

class HYWindow;

typedef void *VOIDPTR;
typedef intptr_t VOIDPTRT;
typedef VOIDPTR WINDOWHANDEL;
typedef VOIDPTR CursorPtr;


struct ApplicationInfo {
  HYString LastError;
  VOIDPTR Instance = nullptr;
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
  FontMgrPtr FontMgr;
  TypefacePtr DefaultTypeface;
  std::unordered_map<HYString, TypefacePtr> FontTable;
};

}

#include "Cursor.h"
#include "Point.h"

#endif //HYGUI_DEFINE_H
