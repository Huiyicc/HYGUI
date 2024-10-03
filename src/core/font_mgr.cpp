//
// Created by 19254 on 24-9-30.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFontMgr.h>
#include <include/core/SkFontMgr.h>

namespace HYGUI {

HYFontMgr::HYFontMgr() {}

HYFontMgr::HYFontMgr(SkFontMgr *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkFontMgr>()) {
      };

HYFontMgr::~HYFontMgr() {

};

SkFontMgr *HYFontMgr::operator->() {
  return m_ptr.get();
};
bool HYFontMgr::operator!() {
  return !m_ptr;
};


}// namespace HYGUI