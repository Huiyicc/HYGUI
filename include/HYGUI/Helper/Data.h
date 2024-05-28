//
// Created by 19254 on 24-5-27.
//

#ifndef HYGUI_DATA_H
#define HYGUI_DATA_H

#include <HYGUI/Helper/Memory.h>
#include <vector>

namespace HYGUI {

struct entry_s {
  size_t hKey;
  _Atomic size_t dwValue;
  struct entry_s *pEntry;
};

typedef void ( *HashTablePROC)(void *);

struct HY_HashTable {
  HashTablePROC pfnDelete;
  _Atomic (struct entry_s *) *pTable;
  size_t dwBound;
  _Atomic size_t dwCount;
  size_t dwThreshold;
};


HY_HashTable *HY_HashTable_Create(size_t dwBound, HashTablePROC pfnDelete);

bool HY_HashTable_Clear(HY_HashTable *hTable);

bool HY_HashTable_Destroy(HY_HashTable *hTable);

void HY_HashTable_ReHash(HY_HashTable *hTable);

bool HY_HashTable_Set(HY_HashTable *hTable, size_t hKey, size_t dwValue);

bool HY_HashTable_Get(HY_HashTable *hTable, size_t hKey, size_t *dwValue);

size_t HY_HashTable_GetCounts(HY_HashTable *hTable);

bool HY_HashTable_Remove(HY_HashTable *hTable, size_t hKey);

bool HY_HashTable_IsExist(HY_HashTable *hTable, size_t hKey);

size_t
HY_HashTable_GetAllKeysAndValues(HY_HashTable *hTable, std::vector<size_t> &aryKey, std::vector<size_t> &aryValue);

}

#endif //HYGUI_DATA_H
