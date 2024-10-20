//
// Created by 19254 on 24-10-18.
//
#include <HYGUI/HYDefine.h>
#include <HYGUI/HYPoint.h>
#include <HYGUI/HYRect.h>
#include <HYGUI/HYString.h>
#include <HYGUI/HYWidget.h>
#include <SDL3/SDL.h>
#include <ranges>


namespace HYGUI {

HYWidget *HYWidget::Make() {
  return new HYWidget{};
}

HYWidget::HYWidget() {
  updateDrawRect();
}

void HYWidget::updateDrawRect() {
  // 更新显示区域信息
  if (!m_parent) {
    // 当前是一级组件
    m_rawRect = {m_x, m_y, m_width, m_height};
    m_visibleRect = {
      std::max(0.0f, m_x),
      std::max(0.0f, m_y),
      std::max(0.0f, m_width - (0 - m_x)),
      std::max(0.0f, m_height - (0 - m_y))};
  } else {
    // 当前是子组件
    // 计算相对于父组件的坐标
    float parentX = m_parent->m_rawRect.x;
    float parentY = m_parent->m_rawRect.y;

    m_rawRect = {parentX + m_x, parentY + m_y, m_width, m_height};

    // 计算实际可见区域，考虑父组件的可见区域
    float visibleX = std::max(m_rawRect.x, m_parent->m_visibleRect.x);
    float visibleY = std::max(m_rawRect.y, m_parent->m_visibleRect.y);
    float visibleWidth = std::min(m_rawRect.x + m_width, m_parent->m_visibleRect.x + m_parent->m_visibleRect.width) - visibleX;
    float visibleHeight = std::min(m_rawRect.y + m_height, m_parent->m_visibleRect.y + m_parent->m_visibleRect.height) - visibleY;

    m_visibleRect = {visibleX, visibleY, visibleWidth, visibleHeight};
  }
  Refresh();
};

void HYWidget::eventHandle(HYWindow *window, HYWidget *widget, HYWidgetEvent event, uint64_t p1, uint32_t p2) {
  if (!m_init) {
    m_init = true;
    if (Events.OnEvent(m_window, m_parent, HYWidgetEvent::HYWidgetEvent_Create, 0, 0) == 0) {
      Events.OnCreate(m_window, m_parent);
    }
  }


}

HYWidget::~HYWidget() {
  for (auto w: m_children) {
    delete w;
  }
}

void HYWidget::Refresh() {
  if (!m_init) {
    return;
  }
  HYObjectPushEvent(m_window,m_parent,HYWidgetEvent_Paint,0,0);
}

HYWidget *HYWidget::AddWidget(HYWidget *child) {
  child->m_window = this->m_window;
  child->m_parent = this;
  return this;
};

HYWidget *HYWidget::AddWidget(std::vector<HYWidget *> &children) {
  for (HYWidget *child: children | std::views::filter([](HYWidget *w) { return w != nullptr && w->m_window == nullptr; })) {
    m_children.emplace_back(child);
    child->m_window = this->m_window;
    child->m_parent = this;
  }
  return this;
};

HYWidget *HYWidget::X(float x) {
  m_x = x;
  updateDrawRect();
  return this;
};

float HYWidget::X() const {
  return m_x;
};

HYWidget *HYWidget::Y(float y) {
  m_y = y;
  updateDrawRect();
  return this;
};

float HYWidget::Y() const {
  return m_y;
};

HYWidget *HYWidget::Point(float x, float y) {
  m_x = x;
  m_y = y;
  updateDrawRect();
  return this;
};

HYWidget *HYWidget::Point(const HYPointf &point) {
  m_x = point.x;
  m_y = point.y;
  updateDrawRect();
  return this;
};

HYWidget *HYWidget::Width(float width) {
  m_width = width;
  updateDrawRect();
  return this;
};

HYWidget *HYWidget::Height(float height) {
  m_height = height;
  updateDrawRect();
  return this;
};

float HYWidget::Width() const {
  return m_width;
};

float HYWidget::Height() const {
  return m_height;
};

HYWidget *HYWidget::Size(float width, float height) {
  m_width = width;
  m_height = height;
  updateDrawRect();
  return this;
};

HYWidget *HYWidget::Rect(float x, float y, float width, float height) {
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
  updateDrawRect();
  return this;
};

HYWidget *HYWidget::Rect(const HYRectf &rect) {
  m_x = rect.x;
  m_y = rect.y;
  m_width = rect.width;
  m_height = rect.height;
  updateDrawRect();
  return this;
};

const HYString &HYWidget::ClassName() {
  return m_ClassName;
};
HYWidget *HYWidget::ClassName(const HYString &className) {
  m_ClassName = className;
  updateDrawRect();
  return this;
};

};// namespace HYGUI