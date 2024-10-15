//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H

#include "HYCursor.h"


#include <HYGUI/HYFontMgr.h>
#include <HYGUI/HYString.h>
#include <HYGUI/HYTypeDef.h>
#include <HYGUI/HYTypeface.h>
#include <cstdint>
#include <memory>
#include <mutex>
#include <set>
#include <unordered_map>


namespace HYGUI {

constexpr const char *EMOJI_NAME = "_default_emoji_";

enum class HYGlobalFlag : uint32_t {
  HYGlobalFlagGraphicNone = 0,
  // HYGlobalFlagGraphicGL,

  HYGlobalFlagGraphicDefault = HYGlobalFlagGraphicNone,
};

class HYWindow;

typedef void *VOIDPTR;
typedef intptr_t VOIDPTRT;

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
  HYCursor Cursor;
  // 默认图标
  VOIDPTR Icon = nullptr;
  // 默认小图标
  VOIDPTR IconSm = nullptr;

  std::vector<std::shared_ptr<HYWindow>> WindowsTable;
  std::mutex WindowsTableMutex;
  uint32_t EventCustomStart;
  uint32_t EventWindow;//起始消息号
  uint32_t EventObject;//起始消息号
  HYFontMgr FontMgr;
  HYTypeface DefaultTypeface;
  HYTypeface EmojiTypeface;// emoji字体
  HYTypeface UtilsTypeface;// 特殊符号字体
  std::unordered_map<HYString, HYTypeface> FontTable;
};

#include <limits>
constexpr int WINDOWCREATEPOINT_USEDEFAULT = std::numeric_limits<int>::max();

}// namespace HYGUI

//#include "Cursor.h"
//#include "Point.h"

#endif//HYGUI_DEFINE_H
