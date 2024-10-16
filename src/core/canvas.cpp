//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include "core/SkRRect.h"
#include <HYGUI/HYCanvas.h>
#include <HYGUI/HYPaint.h>
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

HYCanvas::~HYCanvas() {

};


HYCanvas::HYCanvas() {
  m_ptr = nullptr;
};


HYCanvas::HYCanvas(SkCanvas *ptr)
    : m_ptr(ptr) {};

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

void HYCanvas::DrawRect(HYPaint &paint, const HYRect &rect) {
  m_ptr->drawRect(SkRect::MakeLTRB(rect.x, rect.y, rect.width, rect.height), *paint.get());
}

void HYCanvas::DrawRectf(HYPaint &paint, const HYRectf &rect) {
  m_ptr->drawRect(SkRect::MakeLTRB(rect.x, rect.y, rect.width, rect.height), *paint.get());
}

void HYCanvas::DrawRoundRect(HYPaint &paint, const HYRect &rect, float rx, float ry) {
  m_ptr->drawRoundRect(SkRect::MakeLTRB(rect.x, rect.y, rect.width, rect.height), rx, ry, *paint.get());
}

void HYCanvas::DrawRoundRectf(HYPaint &paint, const HYRectf &rect, float rx, float ry) {
  m_ptr->drawRoundRect(SkRect::MakeLTRB(rect.x, rect.y, rect.width, rect.height), rx, ry, *paint.get());
}

void HYCanvas::ClipRRect(const HYRRect &rrect) {
  SkRRect roundRect;
  roundRect.setRectXY(SkRect::MakeXYWH(rrect.x, rrect.y, rrect.width, rrect.height),
                      rrect.xRad, rrect.yRad);
  m_ptr->clipRRect(roundRect);
}

void HYCanvas::Save() {
  m_ptr->save();
}
void HYCanvas::Restore() {
  m_ptr->restore();
}

void HYCanvas::ResetMatrix() {
  m_ptr->resetMatrix();
}


};// namespace HYGUI
