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


SkPaint *HYPaint::operator->() const {
  return m_ptr.get();
};

bool HYPaint::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}

bool HYPaint::operator!() const {
  return !m_ptr;
};

}// namespace HYGUI