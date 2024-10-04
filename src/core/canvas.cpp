//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYCanvas.h>
#include <include/core/SkCanvas.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYCanvas, SkCanvas);

HYCanvas::~HYCanvas() {

};


HYCanvas::HYCanvas() {
  m_ptr = std::make_shared<SkCanvas>();
};


HYCanvas::HYCanvas(SkCanvas *ptr)
    : m_ptr(ptr) {
      };


};// namespace HYGUI
