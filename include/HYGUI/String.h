//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_STRING_H
#define HYGUI_STRING_H

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
  explicit operator std::wstring();

  std::wstring_view toStdWStringView() const;
  std::string_view toStdStringView() const;

  std::string toStdString()const;

  std::wstring toStdWString()const;

  bool empty() const;

  void clear();

  void append(const char *pData);
  void append(const wchar_t *pData);
  void append(const HYString&str);

private:
  std::wstring m_wstrData;
  std::string m_strData;

};

}

#endif //HYGUI_STRING_H
