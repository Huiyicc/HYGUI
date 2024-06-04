//
// Created by 19254 on 24-6-3.
//
#include "HYGUI/Color.h"

namespace HYGUI {

HYARGB HYColorRgbToArgb(const HYRGB &rgb, uint8_t alpha) {
  HYARGB argb{alpha, rgb.r, rgb.g, rgb.b};
  return argb;
}

HYARGB HYColorRgbToArgb(int rgb, uint8_t alpha) {
  return {alpha, uint8_t((rgb >> 16) & 0xFF), uint8_t((rgb >> 8) & 0xFF), uint8_t(rgb & 0xFF)};
}

HYRGB HYColorArgbToRgb(const HYARGB &argb) {
  HYRGB rgb{argb.r, argb.g, argb.b};
  return rgb;
}

HYRGB HYColorArgbToRgb(int argb) {
  return {uint8_t((argb >> 16) & 0xFF), uint8_t((argb >> 8) & 0xFF), uint8_t(argb & 0xFF)};
}

}