//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFont.h>
#include <include/core/SkFont.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYFont, SkFont);

HYFont::~HYFont(){

};

HYFont::HYFont() {
  m_ptr = std::make_shared<SkFont>();
};

HYFont::HYFont(SkFont *ptr)
    : m_ptr(ptr){};



}// namespace HYGUI
