//
// Created by 19254 on 24-10-1.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYTypeface.h>
#include <include/core/SkTypeface.h>

namespace HYGUI {

HYTypeface::~HYTypeface() {

};

HYTypeface::HYTypeface() {

};
HYTypeface::HYTypeface(SkTypeface *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkTypeface>()) { };

//void HYTypeface::reset(SkTypeface*ptr) {
//  m_ptr.reset(ptr);
//};

bool HYTypeface::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}
SkTypeface *HYTypeface::operator->() const {
  return m_ptr.get();
};
bool HYTypeface::operator!() const {
  return !m_ptr;
};

}// namespace HYGUI
