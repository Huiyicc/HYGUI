//
// Created by 19254 on 24-6-24.
//

#ifndef HYGUI_FONT_H
#define HYGUI_FONT_H

#include "Define.h"

namespace HYGUI {

TypefacePtr HYTypefaceCreateFromDefault();

void HYTypefaceRelease(TypefacePtr font);

FontPtr HYFontCreate();

FontPtr HYFontCreateFromTypeface(TypefacePtr typeface);

void HYFontRelease(FontPtr font);

}

#endif //HYGUI_FONT_H
