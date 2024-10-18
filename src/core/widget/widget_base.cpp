//
// Created by 19254 on 24-10-18.
//
#include <HYGUI/HYDefine.h>
#include <HYGUI/HYPoint.h>
#include <HYGUI/HYRect.h>
#include <HYGUI/HYString.h>
#include <HYGUI/HYWidget.h>


namespace HYGUI {

HYWidget::HYWidget() {
}

HYWidget::~HYWidget() {
  for (auto w: m_children) {
    delete w;
  }
}

HYWidget &HYWidget::X(float x) {
  m_x = x;
  return *this;
};

float HYWidget::X() const {
  return m_x;
};

HYWidget &HYWidget::Y(float y) {
  m_y = y;
  return *this;
};

float HYWidget::Y() const {
  return m_y;
};

HYWidget &HYWidget::Point(float x, float y) {
  m_x = x;
  m_y = y;
  return *this;
};

HYWidget &HYWidget::Point(const HYPointf &point) {
  m_x = point.x;
  m_y = point.y;
  return *this;
};

HYWidget &HYWidget::Width(float width) {
  m_width = width;
  return *this;
};

HYWidget &HYWidget::Height(float height) {
  m_height = height;
  return *this;
};

float HYWidget::Width() const {
  return m_width;
};

float HYWidget::Height() const {
  return m_height;
};

HYWidget &HYWidget::Size(float width, float height) {
  m_width = width;
  m_height = height;
  return *this;
};

HYWidget &HYWidget::Rect(float x, float y, float width, float height) {
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
  return *this;
};

HYWidget &HYWidget::Rect(const HYRectf &rect) {
  m_x = rect.x;
  m_y = rect.y;
  m_width = rect.width;
  m_height = rect.height;
  return *this;
};

const HYString &HYWidget::ClassName() {
  return m_ClassName;
};
HYWidget &HYWidget::ClassName(const HYString &className) {
  m_ClassName = className;
  return *this;
};

};// namespace HYGUI