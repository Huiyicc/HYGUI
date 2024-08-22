//
// Created by 19254 on 24-6-24.
//
#include "HYGUI/Font.h"
#include "PrivateDefinition.h"
#include "include/core/SkFont.h"
#include "include/core/SkTypeface.h"

namespace HYGUI {

FontPtr HYFontCreate() {
  return (SkFont *) HYResourceRegister(ResourceType::ResourceType_Font,
                                       new SkFont(),
                                       "font",
                                       [](void *ptr) {
                                         delete (SkFont *) ptr;
                                       });
}

FontPtr HYFontCreateFromTypeface(TypefacePtr typeface) {
  HYResourceRemoveClearFunc(ResourceType::ResourceType_Typeface, typeface);
  auto f = (SkFont *) HYResourceRegister(ResourceType::ResourceType_Font,
                                         new SkFont(),
                                         "font",
                                         [](void *ptr) {
                                           delete (SkFont *) ptr;
                                         });
  // HYTypefaceRelease(typeface);
  f->setTypeface(sk_sp(typeface));
  return f;
}

void HYFontRelease(FontPtr font) {
  HYResourceRemove(ResourceType::ResourceType_Font, font);
}

}// namespace HYGUI