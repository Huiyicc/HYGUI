//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYCanvas.h>
#include <include/core/SkCanvas.h>

namespace HYGUI {

HYCanvas::~HYCanvas() {

};


HYCanvas::HYCanvas() {};


HYCanvas::HYCanvas(SkCanvas *ptr)
    : m_ptr(ptr) {
      };

SkCanvas *HYCanvas::operator->() const {
  return m_ptr.get();
};

bool HYCanvas::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}

bool HYCanvas::operator!() const {
  return !m_ptr;
};

};// namespace HYGUI
