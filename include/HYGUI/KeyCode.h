//
// Created by 19254 on 24-7-17.
//

#ifndef HYGUI_KEYCODE_H
#define HYGUI_KEYCODE_H

#include <cstdint>

namespace HYGUI {

/**
 * @brief 无
 * */
constexpr const uint32_t HY_KMOD_NONE = 0x0000u;

/**
 * @brief 左Shift键
 * */
constexpr const uint32_t HY_KMOD_LSHIFT = 0x0001u;

/**
 * @brief 右Shift键
 * */
constexpr const uint32_t HY_KMOD_RSHIFT = 0x0002u;

/**
 * @brief 左Ctrl键
 * */
constexpr const uint32_t HY_KMOD_LCTRL = 0x0040u;

/**
 * @brief 右Ctrl键
 * */
constexpr const uint32_t HY_KMOD_RCTRL = 0x0080u;

/**
 * @brief 左Alt键
 * */
constexpr const uint32_t HY_KMOD_LALT = 0x0100u;

/**
 * @brief 右Alt键
 * */
constexpr const uint32_t HY_KMOD_RALT = 0x0200u;

/**
 * @brief 左GUI键
 * */
constexpr const uint32_t HY_KMOD_LGUI = 0x0400u;

/**
 * @brief 右GUI键
 * */
constexpr const uint32_t HY_KMOD_RGUI = 0x0800u;

/**
 * @brief Num Lock键
 * */
constexpr const uint32_t HY_KMOD_NUM = 0x1000u;

/**
 * @brief Caps Lock键
 * */
constexpr const uint32_t HY_KMOD_CAPS = 0x2000u;

/**
 * @brief 模式键
 * */
constexpr const uint32_t HY_KMOD_MODE = 0x4000u;

/**
 * @brief 滚动锁定键
 * */
constexpr const uint32_t HY_KMOD_SCROLL = 0x8000u;

/**
 * @brief Ctrl键
 * */
constexpr const uint32_t HY_KMOD_CTRL = (HY_KMOD_LCTRL | HY_KMOD_RCTRL);

/**
 * @brief Shift键
 * */
constexpr const uint32_t HY_KMOD_SHIFT = (HY_KMOD_LSHIFT | HY_KMOD_RSHIFT);

/**
 * @brief Alt键
 * */
constexpr const uint32_t HY_KMOD_ALT = (HY_KMOD_LALT | HY_KMOD_RALT);

/**
 * @brief GUI键
 * */
constexpr const uint32_t HY_KMOD_GUI = (HY_KMOD_LGUI | HY_KMOD_RGUI);

}// namespace HYGUI

#endif//HYGUI_KEYCODE_H
