//
// Created by 19254 on 24-10-1.
//

#ifndef HYGUI_HYTYPEFACE_H
#define HYGUI_HYTYPEFACE_H

#include <HYGUI/HYFontStyle.h>
#include <HYGUI/HYString.h>
#include <HYGUI/HYMemoryStream.h>
class SkTypeface;

namespace HYGUI {

class HYTypeface : public HYClassBase {
public:
  ~HYTypeface() override;

  explicit HYTypeface();
  explicit HYTypeface(SkTypeface *ptr);

  HYGUICLASS_HANDER_DEFINE(HYTypeface, SkTypeface);

  static HYTypeface MakeFromFile(const char *path);
  static HYTypeface MakeFromFile(const HYString &path);

  static HYTypeface MakeFromLegacyName(const char *name, const HYFontStyle &style = HYFontStyle());
  static HYTypeface MakeFromLegacyName(const HYString &name, const HYFontStyle &style = HYFontStyle());

  static HYTypeface MakeFromStream(HYMemoryStream&& stream);

};


}// namespace HYGUI

#endif//HYGUI_HYTYPEFACE_H
