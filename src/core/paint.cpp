//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYPaint.h>
#include <include/core/SkPaint.h>

namespace HYGUI {

HYPaint::~HYPaint() {

};

HYPaint::HYPaint() {

};

HYPaint::HYPaint(SkPaint *ptr)
    : m_ptr(ptr) {

};


SkPaint *HYPaint::operator->() {
  return m_ptr.get();
};

bool HYPaint::operator!() {
  return !m_ptr;
};

}// namespace HYGUI