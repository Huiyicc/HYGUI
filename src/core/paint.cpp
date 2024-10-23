//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYPaint.h>
#include <include/core/SkPaint.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYPaint, SkPaint);

HYPaint::~HYPaint() {

};

HYPaint::HYPaint() {
  m_ptr = std::make_shared<SkPaint>();
};

HYPaint::HYPaint(SkPaint *ptr)
    : m_ptr(ptr) {

};

void HYPaint::SetColor(const HYARGB&color) {
  m_ptr->setColor(SkColorSetARGB(color.a, color.r, color.g, color.b));
};
void HYPaint::SetColor(const HYRGB &color) {
  m_ptr->setColor(SkColorSetRGB(color.r, color.g, color.b));
}


void HYPaint::SetARGB(const HYARGB&color) {
  m_ptr->setARGB(color.a, color.r, color.g, color.b);
}

void HYPaint::SetARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b){
  m_ptr->setARGB(a, r, g, b);
};

void HYPaint::SetAntiAlias(bool aa) {
  m_ptr->setAntiAlias(aa);
}



}// namespace HYGUI