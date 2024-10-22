//
// Created by 19254 on 24-10-18.
//

#ifndef HYGUI_WIDGET_H
#define HYGUI_WIDGET_H

#include <HYGUI/HYDefine.h>
#include <HYGUI/HYRect.h>
#include <HYGUI/utils/widget_event.h>
#include <memory>

union SDL_Event;

namespace HYGUI {

class HYPointf;
class HYRectf;

#define HYWIDGET_BASEDEFINE_OVERRIDE(T)                           \
  T *X(float x) override {                                        \
    HYWidget::X(x);                                               \
    return this;                                                  \
  };                                                              \
  T *Y(float y) override {                                        \
    HYWidget::Y(y);                                               \
    return this;                                                  \
  };                                                              \
  T *Point(float x, float y) override {                           \
    HYWidget::Point(x, y);                                        \
    return this;                                                  \
  };                                                              \
  T *Point(const HYPointf &point) override {                      \
    HYWidget::Point(point);                                       \
    return this;                                                  \
  };                                                              \
  T *Width(float width) override {                                \
    HYWidget::Width(width);                                       \
    return this;                                                  \
  };                                                              \
  T *Height(float height) override {                              \
    HYWidget::Height(height);                                     \
    return this;                                                  \
  };                                                              \
  T *Size(float width, float height) override {                   \
    HYWidget::Size(width, height);                                \
    return this;                                                  \
  };                                                              \
  T *Rect(float x, float y, float width, float height) override { \
    HYWidget::Rect(x, y, width, height);                          \
    return this;                                                  \
  };                                                              \
  T *Rect(const HYRectf &rect) override {                         \
    HYWidget::Rect(rect);                                         \
    return this;                                                  \
  };                                                              \
  T *ClassName(const HYString &className) override {              \
    HYWidget::ClassName(className);                               \
    return this;                                                  \
  };                                                              \
  T *AddWidget(HYWidget *child) override {                        \
    HYWidget::AddWidget(child);                                   \
    return this;                                                  \
  };                                                              \
  T *AddWidget(std::vector<HYWidget *> &child) override {         \
    HYWidget::AddWidget(child);                                   \
    return this;                                                  \
  };

HYWidget *AddWidget(HYWidget *child);
HYWidget *AddWidget(std::vector<HYWidget *> &child);

class HYWidget : public HYWidgetEventBase {
private:
  bool m_init = false;
  float m_x = 0;
  float m_y = 0;
  float m_height = 0;
  float m_width = 0;
  HYString m_ClassName = WIGDET_DEFAULT_CLASS_NAME;

  HYWindow *m_window = nullptr;// 归属窗口
  HYWidget *m_parent = nullptr;// 父组件
  HYRectf m_rawRect;           // 原始区域(相对于窗口的坐标)
  HYRectf m_visibleRect;       // 实际显示(绘制)区域(相对于窗口的坐标)

  std::vector<HYWidget *> m_children;

  int _event_handel(HYWidgetEvent, int64_t, int64_t);

  void updateDrawRect();

protected:
  HYWidget();
  friend class HYWindow;
  friend void _widget_call_(HYWindow *window, HYWidget *widget, HYWidgetEvent event, int64_t param1, int64_t param2);

public:
  [[nodiscard]] static HYWidget *Make();

  template<class T>
  [[nodiscard]] static T *Make() {
    return new T{};
  };

  ~HYWidget() override;

  [[nodiscard]] virtual float X() const;
  virtual HYWidget *X(float x);
  virtual HYWidget *Y(float y);
  [[nodiscard]] virtual float Y() const;
  virtual HYWidget *Point(float x, float y);
  virtual HYWidget *Point(const HYPointf &point);
  virtual HYWidget *Width(float width);
  virtual HYWidget *Height(float height);
  [[nodiscard]] virtual float Width() const;
  [[nodiscard]] virtual float Height() const;
  virtual HYWidget *Size(float width, float height);
  virtual HYWidget *Rect(float x, float y, float width, float height);
  virtual HYWidget *Rect(const HYRectf &rect);
  virtual const HYString &ClassName();
  virtual HYWidget *ClassName(const HYString &className);

  virtual HYWidget *AddWidget(HYWidget *child);
  virtual HYWidget *AddWidget(std::vector<HYWidget *> &child);

  virtual int MessageEvent(HYWidgetEvent event, int64_t param1, int64_t param2);

  void Refresh();
};


}// namespace HYGUI

#include <HYGUI/utils/widget_function.h>

#endif//HYGUI_WIDGET_H
