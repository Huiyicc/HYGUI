//
// Created by 19254 on 24-10-17.
//

#ifndef HYGUI_HYMOUSE_H
#define HYGUI_HYMOUSE_H

#include <HYGUI/HYPoint.h>

namespace HYGUI {

class HYWindow;

HYPointf HYMouseGetPosition();

HYPointf HYMouseGetPositionFromWindow(HYWindow *window);

}

#endif//HYGUI_HYMOUSE_H
