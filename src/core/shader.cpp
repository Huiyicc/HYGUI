//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYShader.h>
#include <include/core/SkShader.h>

namespace HYGUI {

HYShader::~HYShader() {

};

HYShader::HYShader() {

};

HYShader::HYShader(SkShader *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkShader>()) {

      };


SkShader *HYShader::operator->() {
  return m_ptr.get();
};

bool HYShader::operator!() {
  return !m_ptr;
};


}// namespace HYGUI