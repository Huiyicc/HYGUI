//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_APP_H
#define HYGUI_APP_H

#include "HYGUI/HYDefine.h"

namespace HYGUI {

bool HYInit(HYGlobalFlag DefaultGlobalFlags,
            const HYString&DefaultFont="");


void HYExit();

int HYRun();

}
#endif //HYGUI_APP_H
