//
// Created by 19254 on 24-6-26.
//
#include "HYGUI/Text.h"
#include "PrivateDefinition.h"

namespace HYGUI {

TextBlobBuilderPtr HYTextBlobBuilderCreate() {
  return (TextBlobBuilderPtr) HYResourceRegister(ResourceType::ResourceType_TextBlobBuilder, new SkTextBlobBuilder(), "default text blob builder", [](void *ptr) {
    delete static_cast<SkTextBlobBuilder *>(ptr);
  });
}

void HYTextBlobBuilderDestroy(TextBlobBuilderPtr builder) {
  HYResourceRemove(ResourceType::ResourceType_TextBlobBuilder, builder);
}


}// namespace HYGUI