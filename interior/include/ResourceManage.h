//
// Created by 19254 on 24-6-24.
//

#ifndef HYGUI_RESOURCEMANAGE_H
#define HYGUI_RESOURCEMANAGE_H

#include <functional>

namespace HYGUI {

enum ResourceType : uint32_t {
    // 其它资源
    ResourceType_Other,
    // 窗口
    ResourceType_Window,
    // 子控件
    ResourceType_Object,
    // 光标
    ResourceType_Cursor,
    // 图像
    ResourceType_Image,
    // 字体
    ResourceType_Font,
    // 文本
    ResourceType_Surface,
    // 画布
    ResourceType_Canvas,
    // 画笔
    ResourceType_Paint,
    // 字体
    ResourceType_Typeface,
    // 文本块
    ResourceType_TextBlobBuilder,
    // 着色器
    ResourceType_Shader,
};

extern std::unordered_map<uint32_t, std::string_view> g_resource_type_annotation;

struct ResourceInfo {
    void *Resource = nullptr;
    ResourceType Type;
    HYString AdditionalMessage;
    std::function<void(void *)> DelFunc;
    HYString file;
    int line = 0;
};

void *HYResourceRegister_(ResourceType type, void *resource, const HYString &additional_message = "",
                          std::function<void(void *)> delfunc = nullptr, const char *file = "", int line = 0);

template<typename T>
T _HYResourceRegister_(ResourceType type, T resource, const HYString &additional_message = "",
                       std::function<void(void *)> delfunc = nullptr, const char *file = "", int line = 0) {
  return (T) HYResourceRegister_(type, (void *) resource, additional_message, std::move(delfunc), file, line);
}

bool HYResourceRemove(ResourceType type, void *resource);
bool HYResourceRemoveOther(void *resource);

template<typename T>
T HYResourceRegisterOther_(T resource, const HYString &additional_message, std::function<void(void *)> delfunc,
                           const char *file, int line) {
  if (resource == nullptr) return nullptr;
  HYResourceRegister_(ResourceType::ResourceType_Other, (void *) resource, additional_message, std::move(delfunc), file,
                      line);
  return resource;
}

void HYResourceRemoveClearFunc(ResourceType type, void *resource);

#define HYResourceRegister(type, resource, additional_message, delfunc) _HYResourceRegister_(type, resource, additional_message, delfunc, __FILE__, __LINE__)
#define HYResourceRegisterOther(resource, additional_message, delfunc) HYResourceRegisterOther_(resource, additional_message, delfunc, __FILE__, __LINE__)

void HYResourceDumpDebug();

}// namespace HYGUI

#endif//HYGUI_RESOURCEMANAGE_H
