//
// Created by 19254 on 24-5-14.
//
#include <HYGUI/core/HString.h>

namespace HYGUI {

HString& HString::operator=(const std::wstring& rhs) {
  wstring = rhs;
  return *this;
}

HString& HString::operator=(const char* rhs) {
  wstring = HA2W(rhs);
  return *this;
}

HString& HString::operator+=(const HString& rhs) {
  wstring += rhs.wstring;
  return *this;
}

[[nodiscard]] const std::wstring& HString::toWString() const {
  return wstring;
}

}
