//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/utils/help.h>

#ifdef _HOST_WINDOWS_

#include <windows.h>
#include <memory>

#endif

namespace HYGUI {

void GetWorkingAreaRECT(HRECT *rc) {
  #ifdef _HOST_WINDOWS_
  RECT tmp;
  SystemParametersInfo(SPI_GETWORKAREA, 0, &tmp, 0);
  rc->Left = static_cast<float>(tmp.left);
  rc->Top = static_cast<float>(tmp.top);
  rc->Right = static_cast<float>(tmp.right);
  rc->Bottom = static_cast<float>(tmp.bottom);
  #else
  #error "Not implemented"
  #endif
}

}
