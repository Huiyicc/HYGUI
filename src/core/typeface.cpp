//
// Created by 19254 on 24-10-1.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYTypeface.h>
#include <core/SkFontMgr.h>
#include <core/SkStream.h>
#include <include/core/SkTypeface.h>


namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYTypeface, SkTypeface);

HYTypeface::~HYTypeface(){

};

HYTypeface::HYTypeface(){

};

HYTypeface::HYTypeface(SkTypeface *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkTypeface>()){};

HYTypeface HYTypeface::MakeFromFile(const char *path) {
  return HYTypeface(g_app.FontMgr->makeFromFile(path).release());
};

HYTypeface HYTypeface::MakeFromFile(const HYString &path) {
  return HYTypeface(g_app.FontMgr->makeFromFile(path.data()).release());
};


HYTypeface HYTypeface::MakeFromLegacyName(const char *name, const HYFontStyle &style) {
  return HYTypeface(g_app.FontMgr->legacyMakeTypeface(name, SkFontStyle()).release());
};

HYTypeface HYTypeface::MakeFromLegacyName(const HYString &name, const HYFontStyle &style) {
  return HYTypeface(g_app.FontMgr->legacyMakeTypeface(name.data(), SkFontStyle()).release());
};

HYTypeface HYTypeface::MakeFromStream(HYMemoryStream&& stream) {
  auto rawStreamPtr = stream.release();
  std::unique_ptr<SkStreamAsset> streamAsset(rawStreamPtr.release());

  return HYTypeface(g_app.FontMgr->makeFromStream(std::move(streamAsset)).release());
}

}// namespace HYGUI
