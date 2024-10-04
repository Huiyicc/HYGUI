//
// Created by 19254 on 24-10-3.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYShader.h>
#include <include/core/SkShader.h>

namespace HYGUI {

HYGUICLASS_SRC_DEFINE(HYShader, SkShader);

HYShader::~HYShader() {

};

// HYShader::HYShader() {
//
// };

HYShader::HYShader(SkShader *ptr)
    : m_ptr(ptr, HYPtrDeleter<SkShader>()) {};


}// namespace HYGUI