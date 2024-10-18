//
// Created by 19254 on 24-10-18.
//

#ifndef HYGUI_WIDGET_BUILDER_H
#define HYGUI_WIDGET_BUILDER_H

namespace HYGUI {

struct HYPointf;
struct HYRectf;

class HYWidgetBuilder : public HYClassBase {
  HYWidget *m_widget = nullptr;

public:
  ~HYWidgetBuilder() override;
  HYWidgetBuilder();
  explicit HYWidgetBuilder(const HYString &className = WIGDET_DEFAULT_CLASS_NAME);

  HYWidgetBuilder &X(int x);
  HYWidgetBuilder &Y(int y);
  HYWidgetBuilder &Point(int x, int y);
  HYWidgetBuilder &Point(const HYPointf& point);
  HYWidgetBuilder &Width(int width);
  HYWidgetBuilder &Height(int height);
  HYWidgetBuilder &Size(int width, int height);
  HYWidgetBuilder &Rect(int x, int y, int width, int height);
  HYWidgetBuilder &Rect(const HYRectf &rect);


  HYWidget *Build();
};

}// namespace HYGUI

#endif//HYGUI_WIDGET_BUILDER_H
