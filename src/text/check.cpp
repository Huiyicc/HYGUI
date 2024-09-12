//
// Created by 19254 on 24-8-25.
//
#include "HYGUI/Text.h"
#include "PrivateDefinition.h"
#include <unordered_map>

namespace HYGUI {

bool HYTextCharIsEmoji(char32_t codepoint) {
  auto iter = g_emoji_map.find(codepoint);
  if (iter != g_emoji_map.end()) {
    std::string_view a = std::get<1>(iter->second);
    if (a == "fully-qualified" || a == "component") {
      return true;
    }
  }
  return false;
}

}// namespace HYGUI