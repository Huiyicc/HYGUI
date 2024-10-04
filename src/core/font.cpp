//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFont.h>
#include <include/core/SkFont.h>

namespace HYGUI {

HYFont::~HYFont(){

};

HYFont::HYFont() {
  m_ptr = std::make_shared<SkFont>();
};

HYFont::HYFont(SkFont *ptr)
    : m_ptr(ptr){};

SkFont *HYFont::operator->() const {
  return m_ptr.get();
};


bool HYFont::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}

bool HYFont::operator!() const {
  return !m_ptr;
};


}// namespace HYGUI
