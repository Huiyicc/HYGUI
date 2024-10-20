//
// Created by 19254 on 24-7-26.
//
#include "HYGUI/HYKeyboard.h"
#include "SDL3/SDL_keyboard.h"

namespace HYGUI {

HYKeymod HYKeyboardGetMods() {
    return SDL_GetModState();
}

};
