//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H

#include <HYGUI/HYTypeDef.h>
#include <HYGUI/HYFontMgr.h>
#include <HYGUI/HYTypeface.h>
#include <HYGUI/HYString.h>
#include <cstdint>
#include <mutex>
#include <set>
#include <unordered_map>
#include <memory>

namespace HYGUI {

constexpr const char* EMOJI_NAME = "_default_emoji_";

enum class HYGlobalFlag : uint32_t {
  HYGlobalFlagGraphicNone = 0,
  // HYGlobalFlagGraphicGL,

  HYGlobalFlagGraphicDefault = HYGlobalFlagGraphicNone,
};

class HYWindow;

typedef void *VOIDPTR;
typedef intptr_t VOIDPTRT;
typedef VOIDPTR CursorPtr;


struct ApplicationInfo {
  // 最后错误信息
  HYString LastError;
  // 消息循环锁
  std::mutex LookupLock;
  // 是否正在运行
  bool isRuning = false;
  // 全局标志
  HYGlobalFlag GlobalFlags = HYGlobalFlag::HYGlobalFlagGraphicDefault;
  // 默认类名
  HYString DefaultClassName;
  // 光标
  CursorPtr Cursor = nullptr;
  // 默认图标
  VOIDPTR Icon = nullptr;
  // 默认小图标
  VOIDPTR IconSm = nullptr;

  std::set<HYWindow *> WindowsTable;
  std::mutex WindowsTableMutex;
  uint32_t EventCustomStart;
  uint32_t EventWindow;
  uint32_t EventObject;
  HYFontMgr FontMgr;
  HYTypeface DefaultTypeface;
  HYTypeface EmojiTypeface; // emoji字体
  HYTypeface UtilsTypeface; // 特殊符号字体
  std::unordered_map<HYString, HYTypeface> FontTable;
};

}// namespace HYGUI

//#include "Cursor.h"
//#include "Point.h"

#endif//HYGUI_DEFINE_H
