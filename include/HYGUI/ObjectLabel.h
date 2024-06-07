//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_OBJECTLABEL_H
#define HYGUI_OBJECTLABEL_H

#include "String.h"
#include "Color.h"
#include "Object.h"

namespace HYGUI {

struct HYLabel : public HYObject {

  HYLabel(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height) :
    HYObject{window, parent, x, y, width, height}, Text{text} {}

  HYString Text; // 文本
  HYARGB BackgroundColor; // 背景色
};

typedef HYLabel *HYLabelhandle;

HYLabelhandle
HYLabelCreate(HYWindow *window, HYObjectHandle parent, const wchar_t *text, int x, int y, int width, int height);

void HYLabelSetBackgroundColor(HYLabelhandle label, const HYARGB& color,bool refresh = false);


}

#endif //HYGUI_OBJECTLABEL_H
