//
// Created by 19254 on 24-10-18.
//

#ifndef HYGUI_WIDGET_H
#define HYGUI_WIDGET_H

#include <memory>
#include <HYGUI/utils/widget_event.h>
#include <HYGUI/HYDefine.h>
#include <HYGUI/HYRect.h>

union SDL_Event;

namespace HYGUI {

class HYPointf;
class HYRectf;

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
  HYRectf m_rawRect;      // 原始区域(相对于窗口的坐标)
  HYRectf m_visibleRect;  // 实际显示(绘制)区域(相对于窗口的坐标)

  std::vector<HYWidget *> m_children;

  void updateDrawRect();

  void eventHandle(HYWindow *, HYWidget *, HYWidgetEvent, uint64_t, uint32_t);

protected:
  HYWidget();
  friend class HYWindow;
  friend void _widget_call_(HYWindow *window, HYWidget* widget, HYWidgetEvent event, int64_t param1, int64_t param2);

public:
  [[nodiscard]] static HYWidget *Make();

  ~HYWidget() override;

  HYWidget *X(float x);
  [[nodiscard]] float X() const;
  HYWidget *Y(float y);
  [[nodiscard]] float Y() const;
  HYWidget *Point(float x, float y);
  HYWidget *Point(const HYPointf &point);
  HYWidget *Width(float width);
  HYWidget *Height(float height);
  [[nodiscard]] float Width() const;
  [[nodiscard]] float Height() const;
  HYWidget *Size(float width, float height);
  HYWidget *Rect(float x, float y, float width, float height);
  HYWidget *Rect(const HYRectf &rect);
  const HYString &ClassName();
  HYWidget *ClassName(const HYString &className);

  HYWidget *AddWidget(HYWidget *child);
  HYWidget *AddWidget(std::vector<HYWidget *> &child);

  void Refresh();
};


}// namespace HYGUI

#include <HYGUI/utils/widget_function.h>

#endif//HYGUI_WIDGET_H
