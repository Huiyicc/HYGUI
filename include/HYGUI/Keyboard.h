//
// Created by 19254 on 24-7-26.
//

#ifndef HYGUI_KEYBOARD_H
#define HYGUI_KEYBOARD_H

#include "KeyCode.h"

namespace HYGUI {

/**
 * @brief 键盘ID
 * */
typedef uint32_t HYKeyboardID;

/**
 * @brief 获取当前键盘附加的修饰键状态
 * @return 修饰键状态
 * */
HYKeymod HYKeyboardGetMods();

};

#endif//HYGUI_KEYBOARD_H
