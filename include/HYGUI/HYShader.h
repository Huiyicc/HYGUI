//
// Created by 19254 on 24-10-3.
//

#ifndef HYGUI_HYSHADER_H
#define HYGUI_HYSHADER_H

#include <HYGUI/HYDefine.h>

class SkShader;

namespace HYGUI {

class HYShader : public HYClassBase {
public:
  ~HYShader() override;

  explicit HYShader() = delete;
  explicit HYShader(SkShader *ptr);

  HYGUICLASS_HANDER_DEFINE(HYShader, SkShader);

};

}// namespace HYGUI

#endif//HYGUI_HYSHADER_H
