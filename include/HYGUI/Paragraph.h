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
  std::u32string Ellipsis;
  FontPtr Font;
  float LineSpacing = 3;
  bool AutoWrap = true;// 自动换行
  bool ClearTop = true;// 清除顶部偏移

  HYParagraphBuilderImpl();
  HYParagraphBuilderImpl(const HYRectf &restrict, FontPtr font);
  void AddText(const HYString &);
  void SetAutoWrap(bool auto_wrap);
  bool GetAutoWrap() const;
  void SetClearTop(bool clear_top);
  bool GetClearTop() const;
  void SetLineSpacing(float num);
  float GetLineSpacing();
  HYParagraphHandel Build();
};

class HYParagraph {
public:
  HYParagraph();

  struct CharacterMetrics {
    float_t fAscent = 0;   // 基线到顶部,通常为负值
    float_t fDescent = 0;  // 基线到底部,通常为正值
    float_t fLeading = 0;  // 行间距
    float_t fMaxHeight = 0;// 最大高度 (fMaxHeight = fabs(fAscent) + fabs(fDescent) + fLeading)
  };

  struct CharacterLayout {
    CharacterMetrics metrics;
    HYRectf rect;
    char32_t value = '\0';
    HYString text;
    size_t len = 0;
    bool isEmoji = false;
  };

  struct LineLayout {
    CharacterMetrics metrics;
    HYRectf rect;
    std::vector<CharacterLayout> characterLayouts;
  };

  void Canvas(CanvasPtr canvas,PaintPtr paint, const HYRectf &rect, const HYPointf &offset = {0, 0});

  std::shared_ptr<std::vector<LineLayout>> GetLineLayouts();

  friend HYParagraphBuilderImpl;

private:
  std::shared_ptr<std::vector<LineLayout>> lineLayouts;
  FontPtr font;
};

/**
 * @brief 销毁段落句柄
 *
 * 该函数用于释放与给定段落句柄相关的资源。
 *
 * @param handel 段落句柄，指向需要销毁的段落对象。
 *
 * @note 请确保在调用此函数之前，段落句柄不为NULL。
 */
void HYParagraphDestroy(HYParagraphHandel handel);


}// namespace HYGUI

#endif//HYGUI_PARAGRAPH_H
