//
// Created by 19254 on 24-6-26.
//

#ifndef HYGUI_TEXT_H
#define HYGUI_TEXT_H

#include "TypeDef.h"

namespace HYGUI {

TextBlobBuilderPtr HYTextBlobBuilderCreate();

void HYTextBlobBuilderDestroy(TextBlobBuilderPtr builder);

bool HYTextCharIsEmoji(char32_t codepoint) ;

}

#endif//HYGUI_TEXT_H
