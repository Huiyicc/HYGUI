//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_OBJECTLABEL_H
#define HYGUI_OBJECTLABEL_H

#include "Color.h"
#include "Object.h"
#include "String.h"

namespace HYGUI {

class HYLabel : public HYObject {
public:
  constexpr static const char *ObjectName = "Label";

  HYLabel(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height, HYObjectEventMessageHandel messageEventFunc = nullptr);

  ~HYLabel() override;

  HYString Text;                                   // 文本
  HYARGB TextColor;                                // 文本颜色
  std::vector<HYARGB> BackgroundColors;            // 背景色
  HYGradientMode BanckgroundGradientMode;          // 背景色渐变模式
  HYGradientDirection BanckgroundGradientDirection;// 背景色渐变方向
  FontPtr Font;                                    // 字体
  TextBlobBuilderPtr TextBlobBuilder;              // 文本块构建器
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
HYLabelCreate(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height,HYObjectEventMessageHandel messageEventFunc= nullptr);

void HYLabelSetColorStyle(HYLabelhandle label,
                          HYGradientMode banckgroundGradientMode,          // 背景色渐变模式
                          HYGradientDirection banckgroundGradientDirection,// 背景色渐变方向
                          const std::vector<HYARGB> &banckgroundColors,    // 背景颜色组
                          const HYARGB &textColor,                         // 文本颜色
                          const HYARGB &borderColor,                       // 边框颜色
                          int borderWidth                                  // 边框宽度
);

///**
// * 设置标签控件的背景颜色。
// * @param label 标签控件的句柄，用于指定要设置背景色的控件。
// * @param color 背景颜色值，用于设置标签控件的背景色。
// * @param refresh 是否立即刷新，用于指定是否立即更新控件的显示。
// */
//void HYLabelSetBackgroundColor(HYLabelhandle label, const HYARGB &color, bool refresh = false);


}// namespace HYGUI

#endif//HYGUI_OBJECTLABEL_H
