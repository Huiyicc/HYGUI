//
// Created by 19254 on 24-8-2.
//
#include "HYGUI/Paragraph.h"
#include "PrivateDefinition.h"
#include "boost/algorithm/string.hpp"
#include "core/SkFontMetrics.h"
#include "logs.h"
#include "utfcpp/utf8.h"
#include "utfcpp/utf8/cpp20.h"
#include <string>

namespace HYGUI {

HYParagraphBuilderImpl::HYParagraphBuilderImpl() {
  Ellipsis = U'…';
}

HYParagraphBuilderImpl::HYParagraphBuilderImpl(const HYRectf &restrict, FontPtr font) {
  Restrict = restrict;
  Ellipsis = U'…';
  Font = font;
}

void HYParagraphBuilderImpl::SetAutoWrap(bool auto_wrap) {
  AutoWrap = auto_wrap;
};
bool HYParagraphBuilderImpl::GetAutoWrap() const {
  return AutoWrap;
};

void HYParagraphBuilderImpl::SetClearTop(bool clear_top) {
  ClearTop = clear_top;
};
bool HYParagraphBuilderImpl::GetClearTop() const {
  return ClearTop;
};

void HYParagraphBuilderImpl::AddText(const HYString &str) {
  std::vector<std::string> tmpstr;
  boost::split(tmpstr, str.toStdString(), boost::is_any_of(u8"\n"));
  for (auto &s: tmpstr) {
    TextCache.emplace_back(s);
  }
};

void HYParagraphBuilderImpl::SetLineSpacing(float num) {
  LineSpacing = num;
};
float HYParagraphBuilderImpl::GetLineSpacing() {
  return LineSpacing;
};

HYParagraphHandel HYParagraphBuilderImpl::Build() {
  auto layouts = std::make_shared<std::vector<HYParagraph::LineLayout>>();
  // 获取测量字体的度量信息
  SkFontMetrics font_metrics{};
  Font->getMetrics(&font_metrics);
  auto emoji_font = SkFont(g_app.EmojiTypeface->makeClone(SkFontArguments{}), Font->getSize());
  SkFontMetrics emoji_font_metrics{};
  emoji_font.getMetrics(&emoji_font_metrics);
  // 对每行字体进行挨个测量
  float_t addLen = 0;   // 叠加计算的文本长度偏移
  float_t addHeight = 0;// 叠加计算的文本高度偏移

  for (auto textLayout: TextCache) {
    HYParagraph::LineLayout lineLayout;
    if (textLayout.empty()) {
      textLayout = U" ";
    }
    // 计算每个字符
    textLayout.forEachUtf8CharBoundary([&](const char8_t *data, size_t start, size_t len, char32_t c) -> int {
      // 取出每个符号进行测量
      HYString tests(c);
      auto tests_c = c;
      switch (c) {
        case U'\n': {
          // 也许暂时不需要?
          PrintError("未处理的换行符!!!");
        } break;
        case U' ': {
          // 空格,一般会无法计算,使用a进行代替计算.
          tests = U"1";
          tests_c = U' ';
          len = tests.size();
        } break;
        default:
          break;
      }
      HYParagraph::CharacterLayout characterLayout;
      SkRect ts;
      SkScalar char_scalar;
      auto GlyphID = Font->unicharToGlyph(c);
      if (GlyphID == 0) {
        // 测量失败,轮到emoji字体了
        GlyphID = emoji_font.unicharToGlyph(c);
        if (GlyphID != 0) {
          char_scalar = emoji_font.measureText(tests.c_str(), len, SkTextEncoding::kUTF8, &ts);
          characterLayout.isEmoji = true;
        } else {
          tests = U'☐';
          tests_c = U'☐';
          len = tests.size();
          char_scalar = Font->measureText(tests.c_str(), len, SkTextEncoding::kUTF8, &ts);
        }
      } else {
        char_scalar = Font->measureText(tests.c_str(), len, SkTextEncoding::kUTF8, &ts);
      }
      //      if(c==U'。') {
      //        PrintDebug("{} {} {}x{} GlyphID:{}",tests.c_str(),char_scalar,ts.width(),ts.height(),GlyphID);
      //      }
      // PrintDebug("{} {} {}x{} GlyphID:{}",tests.c_str(),char_scalar,ts.width(),ts.height(),GlyphID);
      characterLayout.metrics.fAscent = ts.top();
      characterLayout.metrics.fDescent = ts.bottom();
      characterLayout.metrics.fLeading = std::max(font_metrics.fLeading, emoji_font_metrics.fLeading);
      characterLayout.metrics.fMaxHeight = fabs(lineLayout.metrics.fAscent) + fabs(lineLayout.metrics.fDescent) + lineLayout.metrics.fLeading;

      lineLayout.metrics.fAscent = std::min(ts.top(), lineLayout.metrics.fAscent);
      lineLayout.metrics.fDescent = std::max(ts.bottom(), lineLayout.metrics.fDescent);
      lineLayout.metrics.fLeading = std::max(std::max(font_metrics.fLeading, emoji_font_metrics.fLeading), lineLayout.metrics.fLeading);
      characterLayout.len = len;
      characterLayout.value = tests_c;
      characterLayout.text = tests_c;
      characterLayout.rect = {
        .x = addLen,
        .y = addHeight,
        .width = char_scalar,
        .height = ts.height(),
      };
      // 偏移
      addLen += char_scalar;
      lineLayout.characterLayouts.emplace_back(characterLayout);
      return 0;
    });
    lineLayout.metrics.fMaxHeight = std::fabs(lineLayout.metrics.fAscent) + std::fabs(lineLayout.metrics.fDescent) + std::fabs(lineLayout.metrics.fLeading);
    addHeight += lineLayout.metrics.fMaxHeight + LineSpacing;
    addLen = 0;
    layouts->emplace_back(lineLayout);
  }

  auto p = new HYParagraph();
  HYResourceRegister(ResourceType::ResourceType_Paragraph, p, "HYParagraph", [](void *p) { delete (HYParagraph *) p; });
  p->lineLayouts = std::move(layouts);
  p->font = Font;
  return p;
}

HYParagraph::HYParagraph() {
}

std::shared_ptr<std::vector<HYParagraph::LineLayout>> HYParagraph::GetLineLayouts() {
  return lineLayouts;
};

void HYParagraph::Canvas(CanvasPtr canvas, PaintPtr paint, const HYRectf &rect, const HYPointf &offset) {
  auto emoji_font = SkFont(g_app.EmojiTypeface->makeClone(SkFontArguments{}), font->getSize());
  for (auto &line: *lineLayouts) {
    for (auto &word: line.characterLayouts) {
      SkFont *df = font;
      if (word.isEmoji) {
        df = &emoji_font;
      }
      canvas->drawString(word.text.c_str(), offset.x + word.rect.x, offset.y + word.rect.y - line.metrics.fAscent, *df, *paint);
    }
  }
};

void HYParagraphDestroy(HYParagraphHandel handel) {
  HYResourceRemoveClearFunc(ResourceType::ResourceType_Paragraph, handel);
  delete handel;
  HYResourceRemove(ResourceType::ResourceType_Paragraph, handel);
}


}// namespace HYGUI
