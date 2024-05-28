//
// Created by 19254 on 24-5-27.
//

#ifndef HYGUI_MEMORY_H
#define HYGUI_MEMORY_H

#include <cstdint>


namespace HYGUI {

int HY_SetMemory(void* address, intptr_t offset, intptr_t value) ;

bool HY_MemFree(void*hMem);
void* HY_MemAlloc(size_t dwSize, int dwFlags=0);

int16_t __set_short(void *lpAddr, intptr_t offset, int16_t value);
intptr_t __get(void* lpAddr, intptr_t offset);
intptr_t __set(void* lpAddr, intptr_t offset, intptr_t value);

};

#endif //HYGUI_MEMORY_H
