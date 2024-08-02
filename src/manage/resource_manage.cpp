//
// Created by 19254 on 24-6-24.
//
#include "HYGUI/String.h"
#include "ResourceManage.h"
#include "logs.h"
#include <map>
#include <set>
#include <unordered_map>

namespace HYGUI {

std::unordered_map<uint32_t, std::string_view> g_resource_type_annotation = {
  {ResourceType_Other, "其它资源"},
  {ResourceType_Window, "窗口"},
  {ResourceType_Object, "子控件"},
  {ResourceType_Cursor, "光标"},
  {ResourceType_Image, "图像"},
  {ResourceType_Font, "字体"},
  {ResourceType_Surface, "文本"},
  {ResourceType_Canvas, "画布"},
  {ResourceType_Paint, "画笔"},
  {ResourceType_Typeface, "字体"},
  {ResourceType_TextBlobBuilder, "文本块"},
  {ResourceType_Shader, "着色器"},

};

std::unordered_map<ResourceType, std::map<void *, ResourceInfo>> resource_map;

void *HYResourceRegister_(ResourceType type, void *resource, const HYString &additional_message, std::function<void(void *)> delfunc, const char *file, int line) {
  if (resource == nullptr) return nullptr;
  auto &iter = resource_map[type];
  iter[resource] = ResourceInfo{resource, type, additional_message, std::move(delfunc), file, line};
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

bool HYResourceRemoveOther(void *resource) {
  auto &iter = resource_map[ResourceType::ResourceType_Other];
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

void HYResourceDumpDebug() {
  for (auto &iter: resource_map) {
    for (auto &iter1: iter.second) {
      PrintDebug("Resource: {}, Type: {}, Additional: {} by:{}:{}",
                 (uintptr_t) iter1.second.Resource,
                 g_resource_type_annotation[(uint32_t)iter1.second.Type],
                 iter1.second.AdditionalMessage.c_str(),
                 iter1.second.file.c_str(),
                 iter1.second.line);
    }
  }
}

}// namespace HYGUI