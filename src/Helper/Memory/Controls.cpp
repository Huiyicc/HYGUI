//
// Created by 19254 on 24-5-27.
//
#include <HYGUI/Helper/Memory.h>
#include <PrivateDefinition.h>

namespace HYGUI {

int16_t __set_short(void *lpAddr, intptr_t offset, int16_t value) {
  size_t a = (size_t) lpAddr + offset;
  int16_t old = *(int16_t *) a;
  *(int16_t *) a = value;
  return old;
}

intptr_t __get(void* lpAddr, intptr_t offset) {
  size_t a = (size_t)lpAddr + offset;
  return *(intptr_t*)a;
}

intptr_t __set(void* lpAddr, intptr_t offset, intptr_t value) {
  auto a = (size_t*)((size_t)lpAddr + offset);
  intptr_t old = *a;
  *a = value;
  return old;
}

int HY_SetMemory(void *address, intptr_t offset, intptr_t value) {
  if (address == nullptr) return -1;

  auto targetPtr = (intptr_t *) ((char *) address + offset);
  *targetPtr = value;

  return 0;
}

bool HY_MemFree(void *hMem) {
  free(hMem);
  return true;
//  if (hMem != nullptr) {
//    #ifdef _HOST_WINDOWS_
//    return HeapFree(GetProcessHeap(), 0, hMem);
//    #else
//    free(hMem);
//    return true;
//    #endif
//  }
//  return false;
};

void *HY_MemAlloc(size_t dwSize, int dwFlags) {
  return malloc(dwSize);
//  #ifdef _HOST_WINDOWS_
//  if (dwFlags == 0) {
//    dwFlags = LMEM_ZEROINIT;
//  }
//  return HeapAlloc(GetProcessHeap(), 8, dwSize);
//  #else
//  void *ptr = malloc(dwSize);
//  if (ptr && dwFlags == 0) {
//    memset(ptr, 0, dwSize);
//  }
//  return ptr;
//  #endif
}

};