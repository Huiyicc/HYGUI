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
  uint8_t r=0, g=0, b=0;
};

/**
 * @brief 定义ARGB颜色结构体
 *
 * 该结构体用于表示透明度、红、绿、蓝四种颜色分量的值，
 * 其中透明度（alpha）的取值范围为0到255。
 */
struct HYARGB {
  uint8_t a=0, r=0, g=0, b=0;
};

HYRGB HYColorGenRGB(uint8_t r, uint8_t g,uint8_t b);
HYARGB HYColorGenARGB(uint8_t r, uint8_t g,uint8_t b,uint8_t a=255);

/**
 * @brief 将颜色值从HYColor格式转换为RGB格式。
 *
 * @param color 输入的HYColor颜色值。
 * @return HYRGB 转换后的RGB颜色值。
 */
HYRGB HYColorToRGB(uint32_t color);

/**
 * @brief 将颜色值从HYColor格式转换为ARGB格式。
 *
 * @param color 输入的HYColor颜色值。
 * @return HYARGB 转换后的ARGB颜色值。
 */
HYARGB HYColorToARGB(uint32_t color);

/**
 * @brief 将RGB颜色值转换为整型。
 *
 * @param rgb 输入的RGB颜色值。
 * @return int 转换后的整型颜色值。
 */
int HYColorRGBToInt(HYRGB rgb);

/**
 * @brief 将ARGB颜色值转换为整型。
 *
 * @param argb 输入的ARGB颜色值。
 * @return int 转换后的整型颜色值。
 */
int HYColorARGBToInt(HYARGB argb);

/**
 * @brief 将ARGB颜色值转换为RGB颜色值。
 *
 * @param argb 输入的ARGB颜色值。
 * @return HYRGB 转换后的RGB颜色值。
 */
HYRGB HYColorARGBToRGB(HYARGB argb);

/**
 * @brief 将ARGB颜色值转换为RGB颜色值。
 *
 * @param argb 输入的ARGB颜色值。
 * @return HYRGB 转换后的RGB颜色值。
 */
HYRGB HYColorARGBToRGB(uint32_t argb);

/**
 * @brief 将RGB颜色值转换为ARGB颜色值。
 *
 * @param rgb 输入的RGB颜色值。
 * @param a   透明度值。
 * @return HYARGB 转换后的ARGB颜色值。
 */
HYARGB HYColorRGBToARGB(HYRGB rgb,uint8_t a);

/**
 * @brief 将RGB颜色值转换为ARGB颜色值。
 *
 * @param rgb 输入的RGB颜色值。
 * @param a   透明度值。
 * @return HYARGB 转换后的ARGB颜色值。
 */
HYARGB HYColorRGBToARGB(uint32_t rgb,uint8_t a);
/**
 * 将RGB颜色值转换为ARGB颜色值。
 *
 * @param rgb 输入的RGB颜色值，格式为RRGGBB。
 * @param a 输入的Alpha透明度值，范围为0-255。
 * @return 返回转换后的ARGB颜色值，格式为AARRGGBB。
 */
int HYColorRGBToARGBInt(uint32_t rgb,uint8_t a);

/**
 * 将ARGB颜色值转换为RGB颜色值。
 *
 * @param argb 输入的ARGB颜色值，格式为AARRGGBB。
 * @return 返回转换后的RGB颜色值，格式为RRGGBB。
 */
int HYColorARGBToRGBInt(uint32_t argb);

}

#endif //HYGUI_COLOR_H
