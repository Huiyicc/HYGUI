//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYCanvas.h>
#include <HYGUI/HYSurface.h>
#include <include/core/SkSurface.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYSurface, SkSurface);

HYSurface::~HYSurface() {

};
//
// HYSurface::HYSurface() {
//
// };

HYSurface::HYSurface(SkSurface *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkSurface>()) {

      };

HYCanvas HYSurface::GetCanvas() {
  return HYCanvas{m_ptr->getCanvas()};
}

}// namespace HYGUI
