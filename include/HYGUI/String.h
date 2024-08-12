//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_STRING_H
#define HYGUI_STRING_H

// class SkString;
#include <memory>
#include <string>
#include <functional>

namespace HYGUI {

class HYString {
public:

  /**
   * @brief 遍历UTF-8字符的边界。
   *
   * @param data 原始utf8字符串
   * @param start 起始位置
   * @param len 字符长度
   * @param c utf32字符
   * @return 返回-1则终止遍历
   * */
  typedef std::function<int(const char8_t *data,size_t start, size_t len, char32_t c)> ForEachCharHandel;

  HYString();
  HYString(const char *pData);
  HYString(const char8_t *pData);
  HYString(const char8_t *pData, size_t len);
  HYString(const HYString &str);
  HYString(const std::string &str);
  HYString(const char32_t *pData, size_t len);
  HYString(char32_t pData);
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
  void append(const char *pData, size_t len);
  void append(const char8_t *pData, size_t len);
  void append(const HYString &str);
  const char *c_str() const;

  /**
   * 遍历UTF-8字符的边界。
   *
   * 该函数通过回调函数的形式，对输入字符串中的每个UTF-8字符的边界进行处理。UTF-8字符的边界是指字符的起始位置和字符的长度。
   * 对于每个字符，回调函数会被调用一次，传入字符的起始位置和该字符的字节长度。
   *
   * @param callback 一个函数对象，它接受两个参数：字符的起始位置和字符的长度。这个函数对象会在每个字符的边界被调用。
   * @return 返回遍历的字符总数。
   */
  size_t forEachUtf8CharBoundary(const ForEachCharHandel&);

private:
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
