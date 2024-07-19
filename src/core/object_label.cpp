//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Font.h"
#include "HYGUI/ObjectLabel.h"
#include "HYGUI/Paint.h"
#include "HYGUI/Shader.h"
#include "HYGUI/Text.h"
#include "PrivateDefinition.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkTypeface.h"
#include "logs.h"
#include <core/SkFont.h>


namespace HYGUI {

HYLabel::~HYLabel() {
  HYFontRelease(Font);
  HYTextBlobBuilderDestroy(TextBlobBuilder);
}

int label_event_left_down(HYWindow *window, HYObject *obj, int x, int y, int function_key) {

  return 0;
}

void label_paint_draw_banckground(HYLabel *label, PaintPtr paint) {
  // 渐变模式
  ShaderPtr shader = nullptr;
  if (label->BanckgroundGradientMode == HYGradientMode::HYGradientModeLinear) {
    // 线性渐变
    std::vector<HYPoint> pos = {{0, 0}, {label->Width, 0}};
    // 位置
    std::vector<float> scalars(label->BackgroundColors.size());
    for (int i = 0; i < label->BackgroundColors.size(); i++) {
      scalars[i] = float(i) / float(label->BackgroundColors.size() - 1);
    }
    if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionLeftToRight) {
      // 从左到右
      pos[1] = {label->Width, 0};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionRightToLeft) {
      // 从右到左
      // 直接交换colors
      std::reverse(label->BackgroundColors.begin(), label->BackgroundColors.end());
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionTopToBottom) {
      // 从上到下
      pos[1] = {0, label->Height};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionBottomToTop) {
      // 从下到上
      pos[0] = {0, label->Height};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionTopLeftToBottomRight) {
      // 从左上到右下
      pos[1] = {label->Width, label->Height};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionTopRightToBottomLeft) {
      // 从右上到左下
      pos[0] = {label->Width, 0};
      pos[1] = {0, label->Height};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionBottomLeftToTopRight) {
      // 从左下到右上
      pos[0] = {0, label->Height};
      pos[1] = {label->Width, 0};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionBottomRightToTopLeft) {
      // 从右下到左上
      pos[0] = {label->Width, label->Height};
      pos[1] = {0, 0};
    }
    shader = HYShaderCreateLinearGradient(label->BackgroundColors, pos, scalars);

  } else if (label->BanckgroundGradientMode == HYGradientMode::HYGradientModeRadial) {
    // 径向渐变
    std::vector<HYPoint> pos = {{label->Width / 2, label->Height / 2}, {label->Width / 2, label->Height / 2}};
    // 位置
    std::vector<float> scalars(label->BackgroundColors.size());
    for (int i = 0; i < label->BackgroundColors.size(); i++) {
      scalars[i] = float(i) / float(label->BackgroundColors.size() - 1);
    }
    if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionLeftToRight) {
      // 从左到右
      pos[1] = {(label->Width), (label->Height) / 2};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionRightToLeft) {
      // 从右到左
      pos[0] = {(label->Width), (label->Height) / 2};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionTopToBottom) {
      // 从上到下
      pos[1] = {(label->Width) / 2, (label->Height)};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionBottomToTop) {
      // 从下到上
      pos[0] = {(label->Width) / 2, (label->Height)};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionTopLeftToBottomRight) {
      // 从左上到右下
      pos[1] = {(label->Width), (label->Height)};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionTopRightToBottomLeft) {
      // 从右上到左下
      pos[0] = {(label->Width), 0};
      pos[1] = {0, (label->Height)};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionBottomLeftToTopRight) {
      // 从左下到右上
      pos[0] = {0, (label->Height)};
      pos[1] = {(label->Width), 0};
    } else if (label->BanckgroundGradientDirection == HYGradientDirection::HYGradientDirectionBottomRightToTopLeft) {
      // 从右下到左上
      pos[0] = {(label->Width), (label->Height)};
      pos[1] = {0, 0};
    }
    //    shader = SkGradientShader::MakeRadial(pts[0], float(label->Width) / 2, colors.data(), pos.data(), colors.size(), SkTileMode::kClamp);
    //    paint->setShader(shader);
    shader = HYShaderCreateRadialGradient(label->BackgroundColors, float(std::min(label->Width, label->Height)) / 2, pos, scalars);

  } else if (label->BanckgroundGradientMode == HYGradientMode::HYGradientModeSweep) {
    // 扫描渐变
    std::vector<HYPoint> pos = {{(label->Width) / 2, (label->Height) / 2}, {(label->Width) / 2, (label->Height) / 2}};
    // 位置
    std::vector<float> scalars(label->BackgroundColors.size());
    for (int i = 0; i < label->BackgroundColors.size(); i++) {
      scalars[i] = float(i) / float(label->BackgroundColors.size() - 1);
    }
    shader = HYShaderCreateSweepGradient(label->BackgroundColors, pos, scalars);
  } else {
    // 纯色
    HYPaintSetColor(paint, label->BackgroundColors.empty() ? HYARGB{0} : label->BackgroundColors[0]);
  }
  HYPaintSetShader(paint, shader);
  auto bgrect = HYRect{0, 0, label->Width, label->Height};
  HYPaintDrawRect(label->Canvas, paint, &bgrect);
  // 背景绘制完成,清除shader
  HYPaintSetShader(paint, nullptr);
}


int label_event_paint(HYWindow *window, HYObject *object) {
  auto paint = HYObjectBeginPaint(object);
  auto label = reinterpret_cast<HYLabel *>(object);

  // 绘制背景
  label_paint_draw_banckground(label, paint);

  // 绘制字体
  auto text = label->Text.toStdStringView().data();

  SkRect bounds;
  label->Font->measureText(text, label->Text.size(), SkTextEncoding::kUTF8, &bounds);
  SkScalar offsetY = bounds.height();

  auto blb = SkTextBlob::MakeFromString(text, *label->Font);

  HYPaintSetColor(paint, label->TextColor);
  object->Canvas->drawString(label->Text.toStdStringView().data(), 0, offsetY, *label->Font, *paint);

  HYObjectEndPaint(object, paint);
  return 0;
}

HYLabel::HYLabel(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height, HYObjectEventMessageHandel messageEventFunc)
    : HYObject{window, parent, x, y, width, height, ObjectName, "", 0, std::move(messageEventFunc)}, Text{text} {
  RegisterEventPaintCallback(label_event_paint);
  RegisterEventLeftDownCallback(label_event_left_down);
  Font = HYFontCreateFromTypeface(HYTypefaceCreateFromDefault());
  Font->setEdging(SkFont::Edging::kAlias);
  Font->setSize(12);
  TextBlobBuilder = HYTextBlobBuilderCreate();
  BanckgroundGradientMode = HYGradientMode::HYGradientModeNone;
  BanckgroundGradientDirection = HYGradientDirection::HYGradientDirectionNone;
}

HYLabelhandle
HYLabelCreate(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height) {
  auto label = new HYLabel{window, parent, text, x, y, width, height};
  return HYResourceRegister(ResourceType::ResourceType_Object, label, "Label", [](void *ptr) {
    delete reinterpret_cast<HYLabel *>(ptr);
  });
}


void HYLabelSetColorStyle(HYLabelhandle label,
                          HYGradientMode banckgroundGradientMode,          // 背景色渐变模式
                          HYGradientDirection banckgroundGradientDirection,// 背景色渐变方向
                          const std::vector<HYARGB> &banckgroundColors,    // 背景颜色组
                          const HYARGB &textColor,                         // 文本颜色
                          const HYARGB &borderColor,                       // 边框颜色
                          int borderWidth                                  // 边框宽度
) {
  label->TextColor = textColor;
  label->BanckgroundGradientMode = banckgroundGradientMode;
  label->BanckgroundGradientDirection = banckgroundGradientDirection;
  label->BackgroundColors = banckgroundColors;
}

//void HYLabelSetBackgroundColor(HYLabelhandle label, const HYARGB &color, bool refresh) {
//  label->BackgroundColor = color;
//  if (refresh) {
//    HYObjectRefresh(label);
//  }
//}


}// namespace HYGUI