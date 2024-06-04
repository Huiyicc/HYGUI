//
// Created by 19254 on 24-6-3.
//

#ifndef HYGUI_COLOR_H
#define HYGUI_COLOR_H

#include <cstdint>

namespace HYGUI {


/**
 * @brief 定义RGB颜色结构体
 *
 * 该结构体用于表示红绿蓝三种颜色分量的值，
 * 每个分量的取值范围为0到255。
 */
struct HYRGB {
  unsigned char r=0, g=0, b=0;
  operator uint32_t () const {
    return (r << 16) | (g << 8) | b;
  }
  operator int () const {
    return (r << 16) | (g << 8) | b;
  }
};

/**
 * @brief 定义ARGB颜色结构体
 *
 * 该结构体用于表示透明度、红、绿、蓝四种颜色分量的值，
 * 其中透明度（alpha）的取值范围为0到255。
 */
struct HYARGB {
  unsigned char a=0, r=0, g=0, b=0;
  operator uint32_t () const {
    return (a << 24) | (r << 16) | (g << 8) | b;
  }
  operator int () const {
    return (a << 24) | (r << 16) | (g << 8) | b;
  }
};

/**
 * @brief 将RGB颜色转换为ARGB颜色
 *
 * @param rgb 输入的RGB颜色
 * @param alpha 透明度值，默认为255（不透明）
 * @return HYARGB 转换后的ARGB颜色
 *
 * 该函数将一个RGB颜色转换为ARGB颜色，其中透明度分量a可以由参数alpha指定，
 * 默认为不透明。
 */
HYARGB HYColorRgbToArgb(const HYRGB& rgb,uint8_t alpha = 255);

/**
 * @brief 将RGB颜色转换为ARGB颜色
 *
 * @param rgb 输入的RGB颜色
 * @param alpha 透明度值，默认为255（不透明）
 * @return HYARGB 转换后的ARGB颜色
 *
 * 该函数将一个RGB颜色转换为ARGB颜色，其中透明度分量a可以由参数alpha指定，
 * 默认为不透明。
 */
HYARGB HYColorRgbToArgb(int rgb,uint8_t alpha = 255);

/**
 * @brief 将ARGB颜色转换为RGB颜色
 *
 * @param argb 输入的ARGB颜色
 * @return HYRGB 转换后的RGB颜色
 *
 * 该函数将一个ARGB颜色转换为RGB颜色，透明度分量a将被忽略。
 */
HYRGB HYColorArgbToRgb(const HYARGB& argb);

/**
 * @brief 将ARGB颜色转换为RGB颜色
 *
 * @param argb 输入的ARGB颜色
 * @return HYRGB 转换后的RGB颜色
 *
 * 该函数将一个ARGB颜色转换为RGB颜色，透明度分量a将被忽略。
 */
HYRGB HYColorArgbToRgb(int argb);

}

#endif //HYGUI_COLOR_H
