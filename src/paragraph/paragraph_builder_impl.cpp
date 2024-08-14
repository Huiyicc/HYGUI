//
// Created by 19254 on 24-8-2.
//
#include "HYGUI/Paragraph.h"
#include "PrivateDefinition.h"
#include "boost/algorithm/string.hpp"
#include "logs.h"
#include "utfcpp/utf8.h"
#include "utfcpp/utf8/cpp20.h"
#include <string>

namespace HYGUI {

HYParagraphBuilderImpl::HYParagraphBuilderImpl(const HYRectf &restrict, FontPtr font) {
  Restrict = restrict;
  Ellipsis = U'…';
  Font = font;
}

void HYParagraphBuilderImpl::SetAutoWrap(bool auto_wrap) {
  AutoWrap = auto_wrap;
};
bool HYParagraphBuilderImpl::GetAutoWrap() {
  return AutoWrap;
};

void HYParagraphBuilderImpl::SetClearTop(bool clear_top) {
  ClearTop = clear_top;
};
bool HYParagraphBuilderImpl::GetClearTop() {
  return ClearTop;
};

void HYParagraphBuilderImpl::AddText(const HYString &str) {
  std::vector<std::string> tmpstr;
  boost::split(tmpstr, str.toStdString(), boost::is_any_of(u8"\n"));
  for (auto &s: tmpstr) {
    TextCache.emplace_back(s);
  }
};

HYParagraphHandel HYParagraphBuilderImpl::Build() {
  std::vector<HYParagraph::ParagraphLayout> layouts;
  SkRect lastms{0, 0, 0, 0};
  float currentY = 0;
  auto ellipsis_utf8 = utf8::utf32to8(Ellipsis);
  bool overflow = false;

  for (auto &textLayout: TextCache) {
    if (overflow) {
      break;
    }
    HYString currentLine;
    float lineWidth = 0;
    float lineHeight = 0;
    float offTop = 0;

    textLayout.forEachUtf8CharBoundary([&](const char8_t *data, size_t start, size_t len, char32_t c) -> int {
      if (c == U'\n') {
        // 完成当前行的记录
        if (!currentLine.empty()) {
          layouts.push_back({currentLine, {0, currentY, lineWidth, lineHeight}, {0, offTop, 0, 0}});
          currentY += lineHeight;
        }
        currentLine.clear();
        lineWidth = 0;
        lineHeight = 0;
        offTop = 0;
        return 0;
      }

      SkRect ts;
      Font->measureText(data + start, len, SkTextEncoding::kUTF8, &ts);
      if (!layouts.empty()) {
        // 本行第一个字符
        // 检查是否溢出
        if (layouts.back().layout.y + ts.height() > Restrict.height) {
          overflow = true;
          // 删除最后一个
          layouts.pop_back();
          return 1;
        }
      }
      if (AutoWrap && lineWidth + ts.width() > Restrict.width) {
        // 需要换行
        layouts.push_back({currentLine, {0, currentY, lineWidth, lineHeight}, {0, offTop, 0, 0}});
        currentY += lineHeight;
        currentLine = HYString(data + start, len);
        lineWidth = ts.width();
        lineHeight = ts.height();
        offTop = ts.top();
      } else {
        // 继续当前行
        currentLine.append(data + start, len);
        lineWidth += ts.width();
        lineHeight = std::max(lineHeight, ts.height());
        offTop = std::min(ts.top(), offTop);
      }
      return 0;
    });

    if (!currentLine.empty()) {
      layouts.push_back({currentLine, {0, currentY, lineWidth, lineHeight}, {0, offTop, 0, 0}});
      currentY += lineHeight;
    }
  }
  if (ClearTop) {
    for (auto &layout: layouts) {
      layout.layout.y -= layout.offect.y;
      layout.offect.y = 0;
    }
  }
//  for (auto &s: layouts) {
//    PrintDebug("[{},{},{},{}]({},{},{},{}){}",
//               s.layout.x, s.layout.y, s.layout.width, s.layout.height,
//               s.offect.x, s.offect.y, s.offect.width, s.offect.height,
//               s.str.toStdString());
//  }
  auto p = new HYParagraph();
  HYResourceRegister(ResourceType::ResourceType_Paragraph, p, "HYParagraph", [](void *p) { delete (HYParagraph *) p; });
  p->Layouts = std::move(layouts);
  return p;
}

HYParagraph::HYParagraph() {
}

const std::vector<HYParagraph::ParagraphLayout> &HYParagraph::GetLayouts() const {
  return Layouts;
};

void HYParagraphDestroy(HYParagraphHandel handel) {
  HYResourceRemoveClearFunc(ResourceType::ResourceType_Paragraph, handel);
  delete handel;
  HYResourceRemove(ResourceType::ResourceType_Paragraph, handel);
}


}// namespace HYGUI
