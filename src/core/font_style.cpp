//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYFontStyle.h>
#include <include/core/SkFontStyle.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYFontStyle, SkFontStyle);

HYFontStyle::~HYFontStyle() {

};

HYFontStyle::HYFontStyle() {
  m_ptr = std::make_shared<SkFontStyle>();
};

HYFontStyle::HYFontStyle(SkFontStyle *ptr)
    : m_ptr(ptr) {

};

}// namespace HYGUI
