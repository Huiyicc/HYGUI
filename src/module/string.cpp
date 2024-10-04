//
// Created by 19254 on 24-5-31.
//
#include <cstring>
#include <iostream>
#include <string>

#include "HYGUI/HYCoding.h"
#include "HYGUI/HYString.h"
#include "boost/algorithm/string.hpp"
#include "utfcpp/utf8.h"
#include "utfcpp/utf8/cpp20.h"

namespace HYGUI {
using StringBase = std::string;

HYString::~HYString() = default;

HYString::HYString() {
  m_pSkString = std::make_shared<StringBase>();
}

HYString::HYString(const char *pData) {
  m_pSkString = std::make_shared<StringBase>(pData);
}

HYString::HYString(const char8_t *pData) {
  m_pSkString = std::make_shared<StringBase>((char *) pData);
}

HYString::HYString(const char8_t *pData, size_t len) {
  m_pSkString = std::make_shared<StringBase>((char *) pData, len);
}

HYString::HYString(const char32_t *pData, size_t len) {
  std::u32string d(pData, len);
  m_pSkString = std::make_shared<StringBase>();
  utf8::utf32to8(d.begin(), d.end(), std::back_inserter(*m_pSkString));
}

HYString::HYString(char32_t pData) {
  std::u32string d;
  d += pData;
  m_pSkString = std::make_shared<StringBase>();
  utf8::utf32to8(d.begin(), d.end(), std::back_inserter(*m_pSkString));
}


HYString::HYString(const HYString &str) {
  m_pSkString = std::make_shared<StringBase>(*str.m_pSkString);
}

HYString::HYString(const std::string &str) {
  m_pSkString = std::make_shared<StringBase>((char *) str.c_str());
}

HYString &HYString::operator=(const char *pData) {
  *m_pSkString = pData;
  return *this;
}

HYString &HYString::operator=(const char8_t *pData) {
  *m_pSkString = (char *) pData;
  return *this;
}
HYString &HYString::operator=(const char16_t *pData) {
  std::u16string d(pData);
  m_pSkString = std::make_shared<StringBase>();
  utf8::utf16to8(d.begin(), d.end(), std::back_inserter(*m_pSkString));
  return *this;
}
HYString &HYString::operator=(const char32_t *pData) {
  std::u32string d(pData);
  m_pSkString = std::make_shared<StringBase>();
  utf8::utf32to8(d.begin(), d.end(), std::back_inserter(*m_pSkString));
  return *this;
}

HYString &HYString::operator=(const std::string &str) {
  *m_pSkString = str.c_str();
  return *this;
}


HYString &HYString::operator+=(const HYString &str) {
  *m_pSkString += *str.m_pSkString;
  return *this;
}

HYString &HYString::operator+=(const char *pData) {
  *m_pSkString += pData;
  return *this;
}

HYString &HYString::operator+=(const char8_t *pData) {
  *m_pSkString += (char *) pData;
  return *this;
}


HYString HYString::operator+(const HYString &str) {
  HYString ret;
  ret.m_pSkString = std::make_shared<StringBase>(*m_pSkString);
  *ret.m_pSkString += *str.m_pSkString;
  return ret;
}

HYString HYString::operator+(const char *pData) {
  HYString ret;
  ret.m_pSkString = std::make_shared<StringBase>(*m_pSkString);
  *ret.m_pSkString +=  pData;
  return ret;
}

HYString HYString::operator+(const char8_t *pData) {
  HYString ret;
  ret.m_pSkString = std::make_shared<StringBase>(*m_pSkString);
  *ret.m_pSkString += (char *) pData;
  return ret;
}

bool HYString::operator==(const HYString &str) {
  return *m_pSkString == (*str.m_pSkString);
}

bool HYString::operator==(const char *pData) {
  return *m_pSkString == (pData);
}

bool HYString::operator==(const char8_t *pData) {
  return *m_pSkString == (char *) (pData);
}


bool HYString::operator!=(const HYString &str) {
  return !(*m_pSkString == (*str.m_pSkString));
}

bool HYString::operator!=(const char *pData) {
  return !(*m_pSkString ==  (pData));
}

bool HYString::operator!=(const char8_t *pData) {
  return !(*m_pSkString == (char*)(pData));
}


HYString::operator const char *() const {
  return (char *) m_pSkString->c_str();
}

std::string_view HYString::toStdStringView() const {
  return (char *) m_pSkString->data();
}

std::u8string_view HYString::toStdU8StringView() const {
  return (char8_t*)m_pSkString->data();
}

std::string HYString::toStdString() const {
  return (char *) m_pSkString->c_str();
}

std::u8string HYString::toStdU8String() const {
  return (char8_t*)m_pSkString->c_str();
}


HYString &HYString::operator=(const HYString &str) = default;

HYString::operator std::string() {
  return (char *) m_pSkString->c_str();
}

HYString::operator std::u8string() {
  return (char8_t*)m_pSkString->c_str();
}


bool HYString::empty() const {
  return m_pSkString->empty();
}

void HYString::clear() {
  m_pSkString->clear();
}

size_t HYString::size() const {
  return m_pSkString->size();
}

void HYString::append(const char *pData) {
  m_pSkString->append(pData);
}

void HYString::append(const char8_t *str) {
  m_pSkString->append((char *) str);
}

void HYString::append(const char *pData, size_t len) {
  m_pSkString->append(pData, len);
}

void HYString::append(const char8_t *str, size_t len) {
  m_pSkString->append((char *) str, len);
}

void HYString::append(const HYString &str) {
  m_pSkString->append(*str.m_pSkString);
}


const char *HYString::c_str() const {
  return (char *) m_pSkString->c_str();
}

const char *HYString::data() const {
  return (char *) m_pSkString->data();
}

size_t HYString::forEachUtf8CharBoundary(const ForEachCharHandel &func) {
  std::string raw((char *) m_pSkString->data());
  char *w = raw.data();
  char *end = w + raw.length();
  size_t start = 0;
  while (w != end) {
    char *prev = w;
    auto c = utf8::next(w, end);
    size_t len = w - prev;
    if (func(m_pSkString->data(), start, len, c) == -1) {
      break;
    }
    start += len;
  }
  return start;// 返回处理的字符总数
}

void HYString::replace(const char *pData, const char *pReplace) {
  boost::replace_all(*m_pSkString, (char *) pData, (char *) pReplace);
};
void HYString::replace(const char8_t *pData, const char8_t *pReplace) {
  boost::replace_all(*m_pSkString, (char *) pData, (char *) pReplace);
};
void HYString::replace(const char *pData, size_t len, const char *pReplace) {
  boost::replace_all(*m_pSkString, std::string((char *) pData, len), (char *) pReplace);
};
void HYString::replace(const char8_t *pData, size_t len, const char8_t *pReplace) {
  boost::replace_all(*m_pSkString, std::u8string(pData, len), std::u8string(pReplace));
};
void HYString::replace(const HYString &str, const HYString &replace) {
  boost::replace_all(*m_pSkString, *str.m_pSkString, *replace.m_pSkString);
};

void HYString::replace(const size_t start, size_t len, const char *pReplace) {
  m_pSkString->replace(start, len,  pReplace);
};
void HYString::replace(const size_t start, size_t len, const char8_t *pReplace) {
  m_pSkString->replace(start, len,(char *)  pReplace);
};
void HYString::replace(const size_t start, size_t len, const HYString &replace) {
  m_pSkString->replace(start, len, *replace.m_pSkString);
};

void HYString::remove(const char *pData) {
  boost::erase_all(*m_pSkString, (char *) pData);
};
void HYString::remove(const char8_t *pData) {
  boost::erase_all(*m_pSkString, (char *) pData);
};
void HYString::remove(const char *pData, size_t len) {
  boost::erase_all(*m_pSkString, std::string((char *) pData, len));
};
void HYString::remove(const char8_t *pData, size_t len) {
  boost::erase_all(*m_pSkString, std::u8string(pData, len));
};
void HYString::remove(const HYString &str) {
  boost::erase_all(*m_pSkString, *str.m_pSkString);
};

void HYString::insert(size_t pos, const char *pData) {
  m_pSkString->insert(pos, pData);
};
void HYString::insert(size_t pos, const char8_t *pData) {
  m_pSkString->insert(pos, (char *) pData);
};
void HYString::insert(size_t pos, const char *pData, size_t len) {
  m_pSkString->insert(pos, pData, len);
};
void HYString::insert(size_t pos, const char8_t *pData, size_t len) {
  m_pSkString->insert(pos, (char *) pData, len);
};
void HYString::insert(size_t pos, const HYString &str) {
  m_pSkString->insert(pos, *str.m_pSkString);
};

void HYString::erase(size_t pos, size_t len) {
  m_pSkString->erase(pos, len);
};

size_t HYString::find(const char *pData) const {
  return m_pSkString->find( pData);
};
size_t HYString::find(const char8_t *pData) const {
  return m_pSkString->find((char *) pData);
};
size_t HYString::find(const char *pData, size_t len) const {
  return m_pSkString->find( pData, 0, len);
};
size_t HYString::find(const char8_t *pData, size_t len) const {
  return m_pSkString->find((char *) pData, 0, len);
};
size_t HYString::find(const HYString &str) const {
  return m_pSkString->find(*str.m_pSkString);
};

size_t HYString::rfind(const char *pData) const {
  return m_pSkString->rfind( pData);
};
size_t HYString::rfind(const char8_t *pData) const {
  return m_pSkString->rfind((char *) pData);
};
size_t HYString::rfind(const char *pData, size_t len) const {
  return m_pSkString->rfind(pData, 0, len);
};
size_t HYString::rfind(const char8_t *pData, size_t len) const {
  return m_pSkString->rfind((char *) pData, 0, len);
};
size_t HYString::rfind(const HYString &str) const {
  return m_pSkString->rfind(*str.m_pSkString);
};

HYString HYString::substr(size_t pos, size_t len) const {
  HYString ret;
  ret.m_pSkString = std::make_shared<StringBase>(m_pSkString->substr(pos, len));
  return ret;
};

HYString HYString::trim_copy() const {
  HYString ret;
  ret.m_pSkString = std::make_shared<StringBase>(boost::trim_copy(*m_pSkString));
  return ret;
};

HYString& HYString::trim() {
  boost::trim(*m_pSkString);
  return *this;
};

}// namespace HYGUI
