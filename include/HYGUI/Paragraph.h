//
// Created by 19254 on 24-8-2.
//

#ifndef HYGUI_PARAGRAPH_H
#define HYGUI_PARAGRAPH_H

#include "Font.h"
#include "Point.h"

namespace HYGUI {

class HYParagraphBuilderImpl;
class HYParagraph;
typedef HYParagraphBuilderImpl *HYParagraphBuilderImplHandel;
typedef HYParagraph *HYParagraphHandel;

/**
 * @brief 段落构建器
 * */
class HYParagraphBuilderImpl {
public:
  std::vector<HYString> TextCache;
  HYRectf Restrict;
  char32_t Ellipsis;
  FontPtr Font;
  bool AutoWrap = true;// 自动换行
  bool ClearTop = true;// 清除顶部偏移

  HYParagraphBuilderImpl() = delete;
  HYParagraphBuilderImpl(const HYRectf &restrict, FontPtr font);
  void AddText(const HYString &);
  void SetAutoWrap(bool auto_wrap);
  bool GetAutoWrap();
  void SetClearTop(bool clear_top);
  bool GetClearTop();
  HYParagraphHandel Build();
};

class HYParagraph {
public:
  struct ParagraphLayout {
    HYString str;
    HYRectf layout={0};
    HYRectf offect={0};
  };
  HYParagraph();
};


}// namespace HYGUI

#endif//HYGUI_PARAGRAPH_H