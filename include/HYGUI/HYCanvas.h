//
// Created by 19254 on 24-9-30.
//

#ifndef HYGUI_HYCANVAS_H
#define HYGUI_HYCANVAS_H

#include <HYGUI/HYDefine.h>
#include <HYGUI/HYRect.h>

class SkCanvas;

namespace HYGUI {

class HYCanvas : public HYClassBase {
public:
  ~HYCanvas() override;

  explicit HYCanvas();
  explicit HYCanvas(SkCanvas *ptr);
  HYCanvas(const HYCanvas &other);

  void DrawRect(HYPaint &paint, const HYRect &rect);
  void DrawRectf(HYPaint &paint, const HYRectf &rect);
  void DrawRoundRect(HYPaint &paint, const HYRect &rect, float rx, float ry);
  void DrawRoundRectf(HYPaint &paint, const HYRectf &rect, float rx, float ry);

  void ClipRRect(const HYRRect&rrect);

  void Save();
  void Restore();
  void ResetMatrix();

private:
  SkCanvas *m_ptr;

public:
  [[nodiscard]] SkCanvas *get() const;
  SkCanvas *operator->() const;
  bool operator==(const nullptr_t &p) const;
  bool operator!() const;
  HYCanvas &operator=(SkCanvas *other);
  HYCanvas &operator=(const HYCanvas &other);
  explicit operator bool() const;
};

}// namespace HYGUI

#endif//HYGUI_HYCANVAS_H
