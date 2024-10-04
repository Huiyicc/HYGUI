//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFontStyle.h>
#include <include/core/SkFontStyle.h>

namespace HYGUI {

HYFontStyle::~HYFontStyle() {

};

HYFontStyle::HYFontStyle() {

};

HYFontStyle::HYFontStyle(SkFontStyle *ptr)
    : m_ptr(ptr) {

};


SkFontStyle *HYFontStyle::operator->() const {
  return m_ptr.get();
};

bool HYFontStyle::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}

bool HYFontStyle::operator!() const {
  return !m_ptr;
};


}// namespace HYGUI
