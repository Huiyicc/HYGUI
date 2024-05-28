//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_IMAGE_H
#define HYGUI_IMAGE_H

namespace HYGUI {

typedef void* HIMAGE;

HIMAGE HY_ImageLoadFromMemory(void *lpData, size_t dwLen, int uType, int nIndex);

}

#endif //HYGUI_IMAGE_H
