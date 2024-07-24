//
// Created by 19254 on 24-6-9.
//

#ifndef HYGUI_MOUSE_H
#define HYGUI_MOUSE_H

#include "HYGUI/Define.h"

namespace HYGUI {

/**
 * @brief 获取鼠标位置
 *
 * @return HYPointf 鼠标位置
 * */
HYPointf HYMouseGetPosition();

/**
 * @brief 获取鼠标在窗口中的位置
 *
 * @param window 窗口
 * @return HYPointf 鼠标位置
 * */
HYPointf HYMouseGetPositionFromWindow(HYWindow *window);

}

#endif //HYGUI_MOUSE_H
