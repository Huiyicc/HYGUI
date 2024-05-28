//
// Created by 19254 on 24-5-27.
//
#include <map>
#include <HYGUI/Helper/Data.h>
#include <HYGUI/Helper/Memory.h>
#include <vector>
//#include <PrivateDefinition.h>
#include <stdatomic.h>

namespace HYGUI {


HY_HashTable *HY_HashTable_Create(size_t dwBound, HashTablePROC pfnDelete) {
  auto hTable = (HY_HashTable *) malloc(sizeof(HY_HashTable));
  memset(hTable, 0, sizeof(HY_HashTable));
  if (hTable != nullptr) {
    if (dwBound <= 0)
      dwBound = 11;
    auto pTable = (_Atomic (struct entry_s *) *) malloc(dwBound * sizeof(_Atomic (struct entry_s *)));
    if (pTable != nullptr) {
      for (size_t i = 0; i < dwBound; ++i) {
        atomic_store(&pTable[i], NULL);
      }
      hTable->pfnDelete = pfnDelete;
      hTable->pTable = pTable;
      hTable->dwBound = dwBound;
      hTable->dwThreshold = (size_t) (dwBound * 0.72);
    } else {
      free(hTable);
      hTable = nullptr;
    }
  }
  return hTable;
}

bool HY_HashTable_Clear(HY_HashTable *hTable) {
  bool ret = false;
  if (hTable != nullptr) {
    HashTablePROC pfnCbk = hTable->pfnDelete;
    _Atomic (struct entry_s *) *pTable = hTable->pTable;
    size_t dwBound = hTable->dwBound;
    if (pTable != nullptr) {
      for (size_t i = 0; i < dwBound; i++) {
        struct entry_s *pEntry = atomic_load(&pTable[i]);
        while (pEntry != nullptr) {
          struct entry_s *tmp = pEntry;
          pEntry = pEntry->pEntry;
          if (pfnCbk != 0) {
            pfnCbk((void *) tmp->dwValue);
          }
          free(tmp);
        }
        atomic_store(&pTable[i], NULL);
      }
      atomic_store(&(hTable->dwCount), 0);
      ret = true;
    }
  }
  return ret;
}

bool HY_HashTable_Destroy(HY_HashTable *hTable) {
  bool ret = false;
  if (hTable != nullptr) {
    ret = HY_HashTable_Clear(hTable);
    if (ret) {
      HY_MemFree(hTable->pTable);
      HY_MemFree(hTable);
    }
  }
  return ret;
}

size_t HashTable_GetPos(size_t Key, size_t counts) {
  return (Key & 0xFFFFFFFF) % counts;
}

void HY_HashTable_ReHash(HY_HashTable *hTable) {
  _Atomic (struct entry_s *) *oldTable = hTable->pTable;
  size_t oldBound = hTable->dwBound;
  size_t newBound = oldBound * 2 + 1;
  auto newTable = (_Atomic (struct entry_s *) *) malloc(newBound * sizeof(_Atomic (struct entry_s *)));
  for (size_t i = 0; i < newBound; ++i) {
    atomic_store(&newTable[i], nullptr);
  }
  for (size_t i = 0; i < oldBound; i++) {
    struct entry_s *pEntry = atomic_load(&oldTable[i]);
    while (pEntry != nullptr) {
      struct entry_s *oEntry = pEntry;
      pEntry = pEntry->pEntry;
      size_t nPos = HashTable_GetPos(oEntry->hKey, newBound);
      oEntry->pEntry = atomic_exchange(&newTable[nPos], oEntry);
    }
  }
  hTable->pTable = newTable;
  hTable->dwBound = newBound;
  hTable->dwThreshold = (size_t) (newBound * 0.72);
  free(oldTable);
}

bool HY_HashTable_Set(HY_HashTable *hTable, size_t hKey, size_t dwValue) {
  bool ret = false;
  if (hTable != nullptr) {
    size_t nPos = HashTable_GetPos(hKey, hTable->dwBound);
    _Atomic (struct entry_s *) *pTable = hTable->pTable;
    struct entry_s *pEntry = atomic_load(&pTable[nPos]);
    while (pEntry != nullptr) {
      if (pEntry->hKey == hKey) {
        atomic_store(&(pEntry->dwValue), dwValue);
        return true;
      }
      pEntry = pEntry->pEntry;
    }
    if (atomic_load(&hTable->dwCount) >= hTable->dwThreshold) {
      HY_HashTable_ReHash(hTable);
      nPos = HashTable_GetPos(hKey, hTable->dwBound);
      pTable = hTable->pTable;
    }
    pEntry = (struct entry_s *) malloc(sizeof(struct entry_s));
    pEntry->hKey = hKey;
    pEntry->dwValue = dwValue;
    pEntry->pEntry = atomic_exchange(&pTable[nPos], pEntry);
    atomic_fetch_add(&(hTable->dwCount), 1);
    ret = true;
  }
  return ret;
}

bool HY_HashTable_Get(HY_HashTable *hTable, size_t hKey, size_t *dwValue) {
  bool ret = true;
  if (hTable != nullptr) {
    size_t nPos = 0;
    nPos = HashTable_GetPos(hKey, hTable->dwBound);
    void *pTable = hTable->pTable;
    auto pEntry = (entry_s *) __get(pTable, nPos * sizeof(void *));
    while (pEntry != nullptr) {
      if (pEntry->hKey == hKey) {
        *dwValue = pEntry->dwValue;
        ret = true;
        break;
      }
      pEntry = pEntry->pEntry;
    }
  }
  return ret;
}

bool HY_HashTable_Remove(HY_HashTable *hTable, size_t hKey) {
  bool ret = false;
  if (hTable != nullptr) {
    size_t nPos = HashTable_GetPos(hKey, hTable->dwBound);
    _Atomic(struct entry_s*)* pTable = hTable->pTable;
    struct entry_s* pEntry = atomic_load(&pTable[nPos]);
    struct entry_s* prev = nullptr;
    while (pEntry != nullptr) {
      if (pEntry->hKey == hKey) {
        if (prev != nullptr) {
          prev->pEntry = pEntry->pEntry;
        } else {
          atomic_store(&pTable[nPos], pEntry->pEntry);
        }
        atomic_fetch_sub(&(hTable->dwCount), 1);
        HashTablePROC pfn = hTable->pfnDelete;
        if (pfn) {
          pfn((void*)pEntry->dwValue);
        }
        free(pEntry);
        ret = true;
        break;
      }
      prev = pEntry;
      pEntry = pEntry->pEntry;
    }
  }
  return ret;
}

bool HY_HashTable_IsExist(HY_HashTable *hTable, size_t hKey) {
  bool ret = false;
  if (hTable != nullptr)
  {
    size_t nPos = 0;
    nPos = HashTable_GetPos(hKey, hTable->dwBound);
    void* pTable = hTable->pTable;
    entry_s *pEntry = (entry_s *)__get(pTable, nPos * sizeof(void*));
    void* prev = nullptr;
    while (pEntry != nullptr)
    {
      if (pEntry->hKey == hKey)
      {
        ret = true;
        break;
      }
      pEntry = pEntry->pEntry;
    }
  }
  return ret;
}


size_t HY_HashTable_GetCounts(HY_HashTable *hTable) {
  if (hTable != nullptr) {
    return hTable->dwCount;
  }
  return 0;
}

size_t HY_HashTable_GetAllKeysAndValues(HY_HashTable *hTable, std::vector<size_t> &aryKey, std::vector<size_t> &aryValue) {
  size_t dwCount = 0;
  if (hTable != nullptr) {
    auto pTable = hTable->pTable;
    size_t dwBound = hTable->dwBound;
    dwCount = hTable->dwCount;
    if (pTable != nullptr && dwCount > 0) {
      aryKey.resize(dwCount);
      aryValue.resize(dwCount);
      size_t ii = 0;
      for (size_t i = 0; i < dwBound; i++) {
        auto pEntry = (entry_s *) __get(pTable, i * sizeof(void *));
        while (pEntry != nullptr) {
          aryKey[ii] = pEntry->hKey;
          aryValue[ii] = pEntry->dwValue;
          ii++;
          pEntry = pEntry->pEntry;
        }
      }
    }
  }
  return dwCount;
}

}





