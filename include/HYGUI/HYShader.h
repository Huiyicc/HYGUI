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

  explicit HYShader();
  explicit HYShader(SkShader *ptr);

  SkShader *operator->() const;
  bool operator==(const nullptr_t&p) const;
  bool operator!() const;

private:
  std::shared_ptr<SkShader> m_ptr;
};

}// namespace HYGUI

#endif//HYGUI_HYSHADER_H
