//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_STRING_H
#define HYGUI_STRING_H

// class SkString;
#include <memory>
#include <string>

namespace HYGUI {

class HYString {
public:
  HYString();
  HYString(const char *pData);
  HYString(const char8_t *pData);
  HYString(const HYString &str);
  ~HYString();

  HYString &operator=(const HYString &str);
  HYString &operator=(const char8_t *str);
  HYString &operator=(const char *pData);
  HYString &operator=(const std::string &str);

  HYString &operator+=(const HYString &str);
  HYString &operator+=(const char *pData);
  HYString &operator+=(const char8_t *pData);

  HYString operator+(const HYString &str);
  HYString operator+(const char *pData);
  HYString operator+(const char8_t *pData);

  bool operator==(const HYString &str);
  bool operator==(const char *pData);
  bool operator==(const char8_t *pData);

  bool operator!=(const HYString &str);
  bool operator!=(const char *pData);
  bool operator!=(const char8_t *pData);

  explicit operator std::string();
  explicit operator std::u8string();
  operator const char *() const;

  std::string_view toStdStringView() const;
  std::u8string_view toStdU8StringView() const;

  std::string toStdString() const;
  std::u8string toStdU8String() const;

  bool empty() const;

  void clear();
  size_t size() const;

  void append(const char *pData);
  void append(const char8_t *pData);
  void append(const HYString &str);
  const char *c_str() const;

private:
  //  std::wstring m_wstrData;
  //  std::string m_strData;
  std::shared_ptr<std::u8string> m_pSkString;
};

}// namespace HYGUI

namespace std {
template<>
struct hash<HYGUI::HYString> {
  size_t operator()(const HYGUI::HYString &str) const noexcept {
    return hash<std::string>()(str.toStdString());
  }
};
}// namespace std

#endif//HYGUI_STRING_H
