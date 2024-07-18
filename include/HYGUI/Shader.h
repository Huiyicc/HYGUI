//
// Created by 19254 on 24-7-2.
//

#ifndef HYGUI_SHADER_H
#define HYGUI_SHADER_H

#include "HYGUI/TypeDef.h"

namespace HYGUI {

/**
 * 创建一个线性渐变着色器。
 * @param colors 渐变颜色组，用于指定渐变的颜色。
 * @param pos 渐变位置组，用于指定渐变的位置。
 * @param Scalars 渐变比例组，用于指定渐变的比例。
 * @return 返回创建的线性渐变着色器。
 */
ShaderPtr HYShaderCreateLinearGradient(const std::vector<HYARGB> &colors, const std::vector<HYPoint> &pos, const std::vector<float> &Scalars);

/**
 * 创建一个径向渐变着色器。
 * @param colors 渐变颜色组，用于指定渐变的颜色。
 * @param radius 渐变半径，用于指定渐变的半径。
 * @param pos 渐变位置组，用于指定渐变的位置。
 * @param Scalars 渐变比例组，用于指定渐变的比例。
 * @return 返回创建的径向渐变着色器。
 */
ShaderPtr HYShaderCreateRadialGradient(const std::vector<HYARGB> &colors,float radius, const std::vector<HYPoint> &pos, const std::vector<float> &Scalars);

/**
 * 创建一个扫描渐变着色器。
 * @param colors 渐变颜色组，用于指定渐变的颜色。
 * @param pos 渐变位置组，用于指定渐变的位置。
 * @param Scalars 渐变比例组，用于指定渐变的比例。
 * @return 返回创建的扫描渐变着色器。
 * */
ShaderPtr HYShaderCreateSweepGradient(const std::vector<HYARGB> &colors, const std::vector<HYPoint> &pos, const std::vector<float> &Scalars);

}

#endif//HYGUI_SHADER_H
