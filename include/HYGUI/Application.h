//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_APP_H
#define HYGUI_APP_H

#include "HYGUI/Define.h"

namespace HYGUI {

bool HYInit(VOIDPTR ModuleHandle,
            HYGlobalFlag DefaultGlobalFlags,
            CursorPtr DefaultCursor=nullptr,
            HYString DefaultClassName="");

//VOIDPTR HYGetModuleHandle(
//#ifdef _HOST_WINDOWS_
//  VOIDPTR lpModuleName = nullptr
//#else
//#endif
//);

}
#endif //HYGUI_APP_H
