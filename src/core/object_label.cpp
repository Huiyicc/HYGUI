//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/ObjectLabel.h"
#include "logs.h"

namespace HYGUI {

int label_event_paint(HYWindow *window, HYObject *object, HYObjectEvent event, int param1, int param2) {
  auto paint = HYObjectBeginPaint(object);

  auto label = reinterpret_cast<HYLabel *>(object);
  SkRect rect = SkRect::MakeXYWH(0, 0, label->Width, label->Height);
  paint->setColor(SkColorSetARGB(label->BackgroundColor.a,
                                         label->BackgroundColor.r,
                                         label->BackgroundColor.g,
                                         label->BackgroundColor.b));
  object->Canvas->drawRect(rect, *paint);

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
  return label;
}

void HYLabelSetBackgroundColor(HYLabelhandle label, const HYARGB &color, bool refresh) {
  label->BackgroundColor = color;
  if (refresh) {
    HYObjectRefresh(label);
  }
}


}