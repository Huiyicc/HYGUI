//
// Created by 19254 on 24-7-2.
//
#include "HYGUI/Color.h"
#include "HYGUI/Point.h"
#include "HYGUI/Shader.h"
#include "PrivateDefinition.h"
#include <include/effects/SkGradientShader.h>

namespace HYGUI {

ShaderPtr HYShaderCreateLinearGradient(const std::vector<HYARGB> &colors, const std::vector<HYPoint> &pos, const std::vector<float> &Scalars) {
  std::vector<SkColor> lColors;
  lColors.reserve(colors.size());
  for (auto &color: colors) {
    lColors.emplace_back(HYColorARGBToInt(color));
  }
  std::vector<SkPoint> pts;
  pts.reserve(pos.size());
  for (auto &point: pos) {
    pts.emplace_back(SkPoint::Make(point.x, point.y));
  }
  std::vector<SkScalar> scalars;
  scalars.reserve(Scalars.size());
  for (auto &scalar: Scalars) {
    scalars.emplace_back(scalar);
  }
  return HYResourceRegister(ResourceType::ResourceType_Shader, SkGradientShader::MakeLinear(pts.data(), lColors.data(), scalars.data(), lColors.size(), SkTileMode::kClamp).release(), "", nullptr);
}

ShaderPtr HYShaderCreateRadialGradient(const std::vector<HYARGB> &colors,float radius, const std::vector<HYPoint> &pos, const std::vector<float> &Scalars) {
  std::vector<SkColor> lColors;
  lColors.reserve(colors.size());
  for (auto &color: colors) {
    lColors.emplace_back(HYColorARGBToInt(color));
  }
  std::vector<SkPoint> pts;
  pts.reserve(pos.size());
  for (auto &point: pos) {
    pts.emplace_back(SkPoint::Make(point.x, point.y));
  }
  std::vector<SkScalar> scalars;
  scalars.reserve(Scalars.size());
  for (auto &scalar: Scalars) {
    scalars.emplace_back(scalar);
  }
  return HYResourceRegister(ResourceType::ResourceType_Shader, SkGradientShader::MakeRadial(pts[0], radius, lColors.data(), scalars.data(), lColors.size(), SkTileMode::kClamp).release(), "", nullptr);
}

ShaderPtr HYShaderCreateSweepGradient(const std::vector<HYARGB> &colors, const std::vector<HYPoint> &pos, const std::vector<float> &Scalars) {
  std::vector<SkColor> lColors;
  lColors.reserve(colors.size());
  for (auto &color: colors) {
    lColors.emplace_back(HYColorARGBToInt(color));
  }
  std::vector<SkPoint> pts;
  pts.reserve(pos.size());
  for (auto &point: pos) {
    pts.emplace_back(SkPoint::Make(point.x, point.y));
  }
  std::vector<SkScalar> scalars;
  scalars.reserve(Scalars.size());
  for (auto &scalar: Scalars) {
    scalars.emplace_back(scalar);
  }
  return HYResourceRegister(ResourceType::ResourceType_Shader, SkGradientShader::MakeSweep(pts[0].fX, pts[0].fY, lColors.data(), scalars.data(), lColors.size()).release(), "", nullptr);
}


}// namespace HYGUI
