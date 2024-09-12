//
// Created by 19254 on 24-7-31.
//
#include "HYGUI/Layout.h"
#include "include/core/SkFont.h"

namespace HYGUI {

HYRect HYLayoutTestTextRanges(const HYString& str,FontPtr font) {
  HYRect ranges;
  font->measureText(str.c_str(),str.size(),SkTextEncoding::kUTF8);
  return ranges;
}

}// namespace HYGUI
