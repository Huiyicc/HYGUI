//
// Created by 19254 on 24-5-14.
//

#ifndef HYGUI_HSTRING_H
#define HYGUI_HSTRING_H

#include <string>
#include "HYGUI/coding/str.h"

namespace HYGUI {

class HString {
public:
  HString(const char* s) : wstring(HA2W(s)) {}
  HString(const std::string& s) : wstring(HA2W(s)) {}
  HString(std::string_view s) : wstring(HA2W(s)) {}

  template<typename... Args>
  HString(Args&&... args) : wstring(std::forward<Args>(args)...) {}

  HString& operator=(const std::wstring& rhs);

  HString& operator=(const char* rhs);

  HString& operator+=(const HString& rhs);

  [[nodiscard]] const std::wstring& toWString() const;

private:
  std::wstring wstring; // 封装 std::wstring

};

}

#endif //HYGUI_HSTRING_H
