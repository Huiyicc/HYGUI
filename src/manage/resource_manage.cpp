//
// Created by 19254 on 24-6-24.
//
#include "HYGUI/String.h"
#include "ResourceManage.h"
#include <map>
#include <set>
#include <unordered_map>

namespace HYGUI {


std::unordered_map<ResourceType, std::map<void *, ResourceInfo>> resource_map;

void * HYResourceRegister_(ResourceType type, void *resource, const HYString &additional_message, std::function<void(void *)> delfunc, const char *file, int line) {
  if (resource == nullptr) return nullptr;
  auto &iter = resource_map[type];
  iter[resource] = ResourceInfo{resource, type, additional_message, std::move(delfunc)};
  return resource;
};

bool HYResourceRemove(ResourceType type, void *resource) {
  if (resource_map.find(type) == resource_map.end()) return false;
  auto &iter = resource_map[type];
  auto value = iter.find(resource);
  if (value == iter.end()) return false;
  if (value->second.DelFunc != nullptr) value->second.DelFunc(resource);
  iter.erase(resource);
  return true;
};

void HYResourceRemoveClearFunc(ResourceType type, void *resource) {
  if (resource_map.find(type) == resource_map.end()) return;
  auto &iter = resource_map[type];
  auto value = iter.find(resource);
  if (value == iter.end()) return;
  value->second.DelFunc = nullptr;
}

}// namespace HYGUI