//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Font.h"
#include "HYGUI/Layout.h"
#include "HYGUI/ObjectLabel.h"
#include "HYGUI/Paint.h"
#include "HYGUI/Paragraph.h"
#include "HYGUI/Shader.h"
#include "HYGUI/Text.h"
#include "PrivateDefinition.h"
#include "core/SkPath.h"
#include "include/core/SkBlurTypes.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkPaint.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkTypeface.h"
#include "logs.h"
#include "src/text/gpu/StrikeCache.h"
#include <boost/algorithm/string.hpp>
#include <core/SkFont.h>

#include "modules/skparagraph/include/ParagraphBuilder.h"

namespace HYGUI {

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


void label_event_paint_text(HYWindow *window, HYObject *object, PaintPtr paint) {
  auto label = reinterpret_cast<HYLabel *>(object);
  SkRect bounds;
  auto text = label->Text.toStdStringView().data();
  //  auto sc = label->Font->measureText(text, label->Text.size(), SkTextEncoding::kUTF8, &bounds);
  label->Font->measureText(text, label->Text.size(), SkTextEncoding::kUTF8, &bounds);
  // 文本高
  SkScalar line_height = bounds.height();
  std::vector<std::string> draw_texts;
  boost::split(draw_texts, label->Text.toStdStringView(), boost::is_any_of("\n"));
  HYPointf paint_point = {0, line_height};
  HYPaintSetColor(paint, label->TextColor);
//  auto t = g_app.FontMgr->makeFromFile("C:/Users/19254/Downloads/Noto_Color_Emoji/NotoColorEmoji-Regular.ttf");
//  label->Font->setTypeface(t);
  label->Font->setSize(24);


  paint->setAntiAlias(true);
  HYParagraphBuilderImpl ParagraphBuilderImpl(HYRectf{0, 0, static_cast<float>(label->Width), static_cast<float>(label->Height)}, label->Font);

  ParagraphBuilderImpl.SetAutoWrap(true);
  ParagraphBuilderImpl.AddText(label->Text);
  auto paragraph_builder = ParagraphBuilderImpl.Build();
  paragraph_builder->Canvas(object->Canvas,paint,{
    .x = static_cast<float>(label->X),
    .y = static_cast<float>(label->Y),
    .width = static_cast<float>(label->Width),
    .height = static_cast<float>(label->Height),
  });
//  auto text_layouts = paragraph_builder->GetLayouts();
//  //  for (auto &text_layout: text_layouts) {
//  //    object->Canvas->drawString(text_layout.str.c_str(), text_layout.layout.x, text_layout.layout.y, *label->Font, *paint);
//  //
//  //  }
//
//  SkTextBlobBuilder builder;
//  builder.allocRun(*label->Font, 1, 0, 0, &bounds);
//  auto textBlob = builder.make();
//  auto ntc = g_app.FontMgr->makeFromFile(R"(F:\Engcode\c_c++\HYGUI\resource\font\NotoColorEmojiRaw.ttf)");
//  auto f = SkFont(g_app.EmojiTypeface->makeClone(SkFontArguments{}), label->Font->getSize());
//
//  object->Canvas->drawString(label->Text.c_str(), 0, 15,  f, *paint);
//  //auto ntc = g_app.FontMgr->makeFromFile(R"(F:\Engcode\c_c++\HYGUI\resource\font\SourceHanSans-VF.ttf)");
//  auto f = SkFont(ntc, label->Font->getSize());
//  for (auto &text_layout: *text_layouts) {
//
//    object->Canvas->drawString(text_layout.str.c_str(), text_layout.layout.x, text_layout.layout.y,f , *paint);
//    //object->Canvas->drawString(text_layout.str.c_str(), text_layout.layout.x, text_layout.layout.y, *label->Font, *paint);
//    text_layout.str.forEachUtf8CharBoundary([&](const char8_t *data, size_t start, size_t len, char32_t c) -> int {
//      SkPath p;
//      label->Font->setSubpixel(true);
//
//      auto gg = label->Font->getPath(c, &p);
//
//      PrintDebug("gg:{} c:{} len:{}, isemoji:{}", gg, HYString(data + start, len).toStdStringView(),len,HYTextCharIsEmoji(c));
//      return 0;
//    });

//    PrintDebug("c:{}", label->Font->countText(text_layout.str.c_str(), text_layout.str.size(), SkTextEncoding::kUTF8));
//  }


  //  auto blb = SkTextBlob::MakeFromString(text, *label->Font);
}


int label_event_paint(HYWindow *window, HYObject *object) {
  auto paint = HYObjectBeginPaint(object);
  auto label = reinterpret_cast<HYLabel *>(object);

  // 绘制背景
  label_paint_draw_banckground(label, paint);

  // 绘制字体
  label_event_paint_text(window, object, paint);


  HYObjectEndPaint(object, paint);
  return 0;
}

HYLabel::HYLabel(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height, bool visible, HYObjectEventMessageHandel messageEventFunc)
    : HYObject{window, parent, x, y, width, height, true, ObjectName, "", 0, std::move(messageEventFunc)}, Text{text} {
  RegisterEventPaintCallback(label_event_paint);
  RegisterEventLeftDownCallback(label_event_left_down);
  Font = HYFontCreateFromTypeface(HYTypefaceCreateFromDefault());
  Font->setEdging(SkFont::Edging::kAlias);
  Font->setSize(12);
  Typeface = Font->getTypeface();
  //TextBlobBuilder = HYTextBlobBuilderCreate();
  BanckgroundGradientMode = HYGradientMode::HYGradientModeNone;
  BanckgroundGradientDirection = HYGradientDirection::HYGradientDirectionNone;
}

HYLabel::~HYLabel() {
  HYFontRelease(Font);
  HYTypefaceRelease(Typeface);
  //HYTextBlobBuilderDestroy(TextBlobBuilder);
}

HYLabelhandle
HYLabelCreate(HYWindow *window, HYObjectHandle parent, const HYString &text, int x, int y, int width, int height, bool visible, HYObjectEventMessageHandel messageEventFunc) {
  auto label = new HYLabel{window, parent, text, x, y, width, height, visible, std::move(messageEventFunc)};
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