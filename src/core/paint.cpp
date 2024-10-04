//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYPaint.h>
#include <include/core/SkPaint.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYPaint, SkPaint);

HYPaint::~HYPaint() {

};

HYPaint::HYPaint() {
  m_ptr = std::make_shared<SkPaint>();

};

HYPaint::HYPaint(SkPaint *ptr)
    : m_ptr(ptr) {

};


}// namespace HYGUI