//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFont.h>
#include <include/core/SkFont.h>

namespace HYGUI {

HYFont::~HYFont() {

};

HYFont::HYFont() {

};

HYFont::HYFont(SkFont *ptr)
    : m_ptr(ptr) {

      };

SkFont *HYFont::operator->() {
  return m_ptr.get();
};

bool HYFont::operator!() {
  return !m_ptr;
};


}// namespace HYGUI
