//
// Created by 19254 on 24-6-25.
//
#include "HYGUI/Font.h"
#include "PrivateDefinition.h"
#include "include/core/SkFont.h"
#include "include/core/SkTypeface.h"

namespace HYGUI {

TypefacePtr HYTypefaceCreateFromDefault() {
  return (SkTypeface *) HYResourceRegister(ResourceType::ResourceType_Typeface, g_app.DefaultTypeface->makeClone(SkFontArguments()).release(), "default typeface", [](void *ptr) {
    SkSafeUnref((SkTypeface *) ptr);
  });
}

void HYTypefaceRelease(TypefacePtr font) {
  HYResourceRemove(ResourceType::ResourceType_Typeface, font);
}

}// namespace HYGUI