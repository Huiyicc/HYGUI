//
// Created by 19254 on 24-5-28.
//
#include <PrivateDefinition.h>
#include <HYGUI/HYGUI.h>

namespace HYGUI {

void pfnDefaultFreeData(LPVOID dwData) {
  HY_MemFree(dwData);
}

}