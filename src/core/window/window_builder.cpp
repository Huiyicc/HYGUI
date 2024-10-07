//
// Created by 回忆 on 24-10-4.
//
#include <HYGUI/HYWindow.h>
#include <PrivateDefinition.h>

namespace HYGUI {

HYWindowBuilder::HYWindowBuilder(const HYString &title)
    : m_window(new HYWindow{}) {
  m_window->m_title = title;
}

HYWindowBuilder::~HYWindowBuilder() {
}

HYWindowBuilder &HYWindowBuilder::X(int x) {
  m_window->m_x = x;
  return *this;
};

HYWindowBuilder &HYWindowBuilder::Y(int y) {
  m_window->m_y = y;
  return *this;
};

HYWindowBuilder &HYWindowBuilder::Width(int width) {
  m_window->m_width = width;
  return *this;
};

HYWindowBuilder &HYWindowBuilder::Height(int height) {
  m_window->m_height = height;
  return *this;
};

HYWindowBuilder &HYWindowBuilder::Point(const int x, const int y) {
  return X(x).Y(y);
};

HYWindowBuilder &HYWindowBuilder::Size(const int width, const int height) {
  return Width(width).Height(height);
};

HYWindowBuilder &HYWindowBuilder::Rect(int x, int y, int width, int height) {
  return Point(x, y).Size(width, height);
};

HYWindowBuilder &HYWindowBuilder::Title(const HYString &title) {
  m_window->m_title = title;
  return *this;
};

HYWindowBuilder &HYWindowBuilder::BackGroundColor(const HYRGB &color) {
  m_window->m_backGroundColor = HYColorRGBToInt(color);
  return *this;
};

HYWindow *HYWindowBuilder::Build() const {
  std::lock_guard<std::mutex> lock_win_table(g_app.WindowsTableMutex);
  g_app.WindowsTable.push_back(m_window);
  return m_window.get();
};

};
