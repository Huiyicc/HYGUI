//
// Created by 19254 on 24-10-18.
//

#ifndef HYGUI_WIDGET_H
#define HYGUI_WIDGET_H

#include <memory>

namespace HYGUI {

class HYPointf;
class HYRectf;

class HYWidget : public HYClassBase {
private:
  float m_x = 0;
  float m_y = 0;
  float m_height = 0;
  float m_width = 0;
  HYString m_ClassName = WIGDET_DEFAULT_CLASS_NAME;
  std::set<HYWidget*> m_children;

private:
  // friend class HYWidgetBuilder;

public:
  HYWidget();
  ~HYWidget() override;

  HYWidget &X(float x);
  float X() const;
  HYWidget &Y(float y);
  float Y() const;
  HYWidget &Point(float x, float y);
  HYWidget &Point(const HYPointf &point);
  HYWidget &Width(float width);
  HYWidget &Height(float height);
  float Width() const;
  float Height() const;
  HYWidget &Size(float width, float height);
  HYWidget &Rect(float x, float y, float width, float height);
  HYWidget &Rect(const HYRectf &rect);
  const HYString &ClassName();
  HYWidget &ClassName(const HYString &className);
};


}// namespace HYGUI

#endif//HYGUI_WIDGET_H
