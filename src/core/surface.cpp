//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYSurface.h>
#include <include/core/SkSurface.h>

namespace HYGUI {

HYSurface::~HYSurface() {

};

HYSurface::HYSurface() {

};

HYSurface::HYSurface(SkSurface *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkSurface>()) {

};

SkSurface *HYSurface::operator->() {
  return m_ptr.get();
};

bool HYSurface::operator!() {
  return !m_ptr;
};

}// namespace HYGUI
