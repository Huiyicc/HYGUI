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


SkShader *HYShader::operator->() const {
  return m_ptr.get();
};

bool HYShader::operator==(const nullptr_t &p) const {
  return m_ptr == p;
}

bool HYShader::operator!() const {
  return !m_ptr;
};


}// namespace HYGUI