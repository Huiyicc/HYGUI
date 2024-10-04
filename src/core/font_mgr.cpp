//
// Created by 19254 on 24-9-30.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFontMgr.h>
#include <include/core/SkFontMgr.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYFontMgr, SkFontMgr);


HYFontMgr::HYFontMgr() {}

HYFontMgr::HYFontMgr(SkFontMgr *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkFontMgr>()) {
      };

HYFontMgr::~HYFontMgr() {

};



}// namespace HYGUI