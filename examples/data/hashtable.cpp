//
// Created by 19254 on 24-5-27.
//
#include <cstdio>
#include <iostream>
#include "HYGUI/Helper/Data.h"

int main() {
  auto table = HYGUI::HY_HashTable_Create(11, nullptr);
  HYGUI::HY_HashTable_Set(table, 1, 1);
  HYGUI::HY_HashTable_Set(table, 233, 4);
  HYGUI::HY_HashTable_Set(table, 35, 66);
  size_t value;
  HYGUI::HY_HashTable_Get(table, 1, &value);

  std::cout << HYGUI::HY_HashTable_GetCounts(table) << std::endl;
  HYGUI::HY_HashTable_Remove(table, 1);
  std::vector<size_t> keys;
  std::vector<size_t> values;

  HYGUI::HY_HashTable_GetAllKeysAndValues(table, keys, values);
  for (auto &k: keys) {
    std::cout << k << std::endl;
  }
  for (auto &v: values) {
    std::cout << v << std::endl;
  }

  HYGUI::HY_HashTable_Destroy(table);

  return 0;
}