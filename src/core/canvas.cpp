//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYCanvas.h>
#include <include/core/SkCanvas.h>

namespace HYGUI {

bool HYCanvas::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}
SkCanvas *HYCanvas::operator->() const {
  return m_ptr;
};
SkCanvas *HYCanvas::get() const {
  return m_ptr;
};
bool HYCanvas::operator!() const {
  return !m_ptr;
};
HYCanvas::operator bool() const {
  return m_ptr;
}

HYCanvas::~HYCanvas(){

};


HYCanvas::HYCanvas() {
  m_ptr = nullptr;
};


HYCanvas::HYCanvas(SkCanvas *ptr)
    : m_ptr(ptr){};

HYCanvas::HYCanvas(const HYCanvas &other) {
  m_ptr = other.m_ptr;
}
HYCanvas &HYCanvas::operator=(const HYCanvas &other) {
  m_ptr = other.m_ptr;
  return *this;
}

HYCanvas &HYCanvas::operator=(SkCanvas *other) {
  m_ptr = other;
  return *this;
}

};// namespace HYGUI
