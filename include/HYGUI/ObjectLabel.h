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
  constexpr static const wchar_t *ObjectName = L"Label";

  HYLabel(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height) :
    HYObject{window, parent, x, y, width, height, ObjectName}, Text{text} {}

  HYString Text; // 文本
  HYARGB BackgroundColor; // 背景色
  FontPtr Font; // 字体
};


typedef HYLabel *HYLabelhandle;

/**
 * 创建一个标签控件，并返回其句柄。
 * @param window 父窗口指针，用于将标签控件添加到指定窗口。
 * @param parent 父对象句柄，用于指定标签控件的父对象。
 * @param text 初始文本内容，用于设置标签控件显示的文本。
 * @param x 标签控件的x坐标，用于指定控件在窗口中的水平位置。
 * @param y 标签控件的y坐标，用于指定控件在窗口中的垂直位置。
 * @param width 标签控件的宽度，用于指定控件的水平尺寸。
 * @param height 标签控件的高度，用于指定控件的垂直尺寸。
 * @return 返回创建的标签控件的句柄。
 */
HYLabelhandle
HYLabelCreate(HYWindow *window, HYObjectHandle parent, const HYString&text, int x, int y, int width, int height);

/**
 * 设置标签控件的背景颜色。
 * @param label 标签控件的句柄，用于指定要设置背景色的控件。
 * @param color 背景颜色值，用于设置标签控件的背景色。
 * @param refresh 是否立即刷新，用于指定是否立即更新控件的显示。
 */
void HYLabelSetBackgroundColor(HYLabelhandle label, const HYARGB &color, bool refresh = false);


}

#endif //HYGUI_OBJECTLABEL_H
