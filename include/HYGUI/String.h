//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_STRING_H
#define HYGUI_STRING_H

class SkString;
#include <string>

namespace HYGUI {

class HYString {
public:
  HYString();
  HYString(const char *pData);
  HYString(const wchar_t *pData);
  HYString(const HYString &str);
  ~HYString();

  HYString &operator=(const HYString &str);
  HYString &operator=(const char *pData);
  HYString &operator=(const std::string& str);
  HYString &operator=(const wchar_t *pData);
  HYString &operator=(const std::wstring& str);
  HYString &operator+=(const HYString &str);
  HYString &operator+=(const char *pData);
  HYString &operator+=(const wchar_t *pData);
  HYString operator+(const HYString &str);
  HYString operator+(const char *pData);
  HYString operator+(const wchar_t *pData);
  bool operator==(const HYString &str);
  bool operator==(const char *pData);
  bool operator==(const wchar_t *pData);
  bool operator!=(const HYString &str);
  bool operator!=(const char *pData);
  bool operator!=(const wchar_t *pData);
  explicit operator std::string();

  std::string_view toStdStringView() const;

  std::string toStdString()const;

  /**
   * @brief 转换为std::wstring
   * @return std::wstring
   * @note 该函数会将字符串转换为std::wstring,这将会出现一次转码拷贝,请谨慎使用
   * */
  std::wstring toStdWString()const;

  bool empty() const;

  void clear();
  size_t size() const;

  void append(const char *pData);
  void append(const wchar_t *pData);
  void append(const HYString&str);

private:
//  std::wstring m_wstrData;
//  std::string m_strData;
  SkString* m_pSkString;
};

}

namespace std {
template<> struct hash<HYGUI::HYString> {
  size_t operator()(const HYGUI::HYString& str) const noexcept {
    return hash<std::string>()(str.toStdString());
  }
};
}

#endif //HYGUI_STRING_H
