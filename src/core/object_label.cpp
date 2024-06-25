//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Font.h"
#include "HYGUI/ObjectLabel.h"
#include "HYGUI/Paint.h"
#include "PrivateDefinition.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTypeface.h"
#include "logs.h"
#include <core/SkFont.h>

namespace HYGUI {

int label_event_paint(HYWindow *window, HYObject *object, HYObjectEvent event, int param1, int param2) {
  auto paint = HYObjectBeginPaint(object);
  auto label = reinterpret_cast<HYLabel *>(object);
  SkRect rect = SkRect::MakeXYWH(0, 0, label->Width, label->Height);

  // 绘制背景
  HYPaintSetColor(paint, label->BackgroundColor);
  object->Canvas->drawRect(rect, *paint);

  // 绘制字体
  auto text = label->Text.toStdStringView().data();
//  label->Font->setEdging(SkFont::Edging::kAlias);
//  label->Font->setSize(20);
//
//  SkRect bounds;
//  label->Font->measureText(text, label->Text.size(), SkTextEncoding::kUTF8, &bounds);
//  SkScalar offsetY = bounds.height();
//
//  auto blb = SkTextBlob::MakeFromString(text, *label->Font);
//
//  HYPaintSetColor(paint, HYColorGenARGB(120, 120,  210, 255));
//  object->Canvas->drawString(label->Text.toStdStringView().data(), 0, offsetY, *label->Font, *paint);

  HYObjectEndPaint(object, paint);
  return 0;
}

int label_event(HYWindow *window, HYObject *obj, int event, int param1, int param2) {
  if (event == HYObjectEvent_Paint) {
    // 绘制
    label_event_paint(window, obj, (HYObjectEvent) event, param1, param2);
  }
  return 0;
}

HYLabelhandle
HYLabelCreate(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height) {
  auto label = new HYLabel{window, parent, text, x, y, width, height};
  HYObjectAddEventCallback(reinterpret_cast<HYObjectHandle>(label), label_event);
  label->Font = HYFontCreateFromTypeface(HYTypefaceCreateFromDefault());
  return label;
}

void HYLabelSetBackgroundColor(HYLabelhandle label, const HYARGB &color, bool refresh) {
  label->BackgroundColor = color;
  if (refresh) {
    HYObjectRefresh(label);
  }
}


}// namespace HYGUI