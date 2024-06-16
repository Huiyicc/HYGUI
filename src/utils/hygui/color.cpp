//
// Created by 19254 on 24-6-3.
//
#include "HYGUI/Color.h"

namespace HYGUI {

unsigned char IntToColorComponent(uint32_t value) {
  return static_cast<unsigned char>(value & 0xFF);
}

HYRGB HYColorGenRGB(uint8_t r, uint8_t g, uint8_t b) {
  HYRGB t;
  t.b = b;
  t.r = r;
  t.g = g;
  return t;
}

HYARGB HYColorGenARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  HYARGB t;
  t.b = b;
  t.r = r;
  t.g = g;
  t.a = a;
  return t;
}

HYRGB HYColorToRGB(uint32_t color) {
  HYRGB rgb;
  rgb.r = IntToColorComponent(color >> 16);
  rgb.g = IntToColorComponent(color >> 8);
  rgb.b = IntToColorComponent(color);
  return rgb;
}

HYARGB HYColorToARGB(uint32_t color) {
  HYARGB argb;
  argb.a = IntToColorComponent(color >> 24);
  argb.r = IntToColorComponent(color >> 16);
  argb.g = IntToColorComponent(color >> 8);
  argb.b = IntToColorComponent(color);
  return argb;
}

int HYColorRGBToInt(HYRGB rgb) {
  return (rgb.r << 16) | (rgb.g << 8) | rgb.b;
}

int HYColorARGBToInt(HYARGB argb) {
  return (argb.a << 24) | (argb.r << 16) | (argb.g << 8) | argb.b;
}

HYRGB HYColorARGBToRGB(HYARGB argb) {
  HYRGB rgb;
  rgb.r = argb.r;
  rgb.g = argb.g;
  rgb.b = argb.b;
  return rgb;
}

HYRGB HYColorARGBToRGB(uint32_t argb) {
  return HYColorARGBToRGB(HYColorToARGB(argb));
}

int HYColorARGBToRGBInt(uint32_t argb) {
  return HYColorRGBToInt(HYColorARGBToRGB(HYColorToARGB(argb)));
}


HYARGB HYColorRGBToARGB(HYRGB rgb, uint8_t a) {
  HYARGB argb;
  argb.a = a;
  argb.r = rgb.r;
  argb.g = rgb.g;
  argb.b = rgb.b;
  return argb;
}

HYARGB HYColorRGBToARGB(uint32_t rgb, uint8_t a) {
  return HYColorRGBToARGB(HYColorToRGB(rgb), a);
}

int HYColorRGBToARGBInt(uint32_t rgb, uint8_t a) {
  return HYColorARGBToInt(HYColorRGBToARGB(HYColorToRGB(rgb), a));
}


}