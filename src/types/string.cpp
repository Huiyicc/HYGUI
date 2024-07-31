//
// Created by 19254 on 24-5-31.
//
#include <cstring>
#include <iostream>

#include "HYGUI/String.h"
#include "HYGUI/Coding.h"
#include "utfcpp/utf8.h"
#include "utfcpp/utf8/cpp20.h"

namespace HYGUI {
using StringBase = std::u8string;

HYString::~HYString() = default;

HYString::HYString() {
  m_pSkString = std::make_shared<StringBase>();
}

HYString::HYString(const char *pData) {
  m_pSkString = std::make_shared<StringBase>((char8_t *) pData);
}

HYString::HYString(const char8_t *pData) {
  m_pSkString = std::make_shared<StringBase>(pData);
}


HYString::HYString(const HYString &str) {
  m_pSkString = std::make_shared<StringBase>(*str.m_pSkString);
}

HYString &HYString::operator=(const char *pData) {
  *m_pSkString = (char8_t *) pData;
  return *this;
}

HYString &HYString::operator=(const char8_t *pData) {
  *m_pSkString = pData;
  return *this;
}

HYString &HYString::operator=(const std::string &str) {
  *m_pSkString = (char8_t *) str.c_str();
  return *this;
}


HYString &HYString::operator+=(const HYString &str) {
  *m_pSkString += *str.m_pSkString;
  return *this;
}

HYString &HYString::operator+=(const char *pData) {
  *m_pSkString += (char8_t *) pData;
  return *this;
}

HYString &HYString::operator+=(const char8_t *pData) {
  *m_pSkString += pData;
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
  *ret.m_pSkString += (char8_t *) pData;
  return ret;
}

HYString HYString::operator+(const char8_t *pData) {
  HYString ret;
  ret.m_pSkString = std::make_shared<StringBase>(*m_pSkString);
  *ret.m_pSkString += pData;
  return ret;
}

bool HYString::operator==(const HYString &str) {
  return *m_pSkString == (*str.m_pSkString);
}

bool HYString::operator==(const char *pData) {
  return *m_pSkString == (char8_t *) (pData);
}

bool HYString::operator==(const char8_t *pData) {
  return *m_pSkString == (pData);
}


bool HYString::operator!=(const HYString &str) {
  return !(*m_pSkString == (*str.m_pSkString));
}

bool HYString::operator!=(const char *pData) {
  return !(*m_pSkString == (char8_t *) (pData));
}

bool HYString::operator!=(const char8_t *pData) {
  return !(*m_pSkString == (pData));
}


HYString::operator const char *() const {
  return (char *) m_pSkString->c_str();
}

std::string_view HYString::toStdStringView() const {
  return (char *) m_pSkString->data();
}

std::u8string_view HYString::toStdU8StringView() const {
  return *m_pSkString;
}

std::string HYString::toStdString() const {
  return (char *) m_pSkString->c_str();
}

std::u8string HYString::toStdU8String() const {
  return *m_pSkString;
}


HYString &HYString::operator=(const HYString &str) = default;

HYString::operator std::string() {
  return (char *) m_pSkString->c_str();
}

HYString::operator std::u8string() {
  return *m_pSkString;
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
  m_pSkString->append((char8_t *) pData);
}


void HYString::append(const HYString &str) {
  m_pSkString->append(*str.m_pSkString);
}

void HYString::append(const char8_t *str) {
  m_pSkString->append(str);
}

const char *HYString::c_str() const {
  return (char *) m_pSkString->c_str();
}

size_t HYString::forEachUtf8CharBoundary(const std::function<void(size_t start, size_t len)>& func) {
  std::string raw((char *) m_pSkString->data());
  char *w = raw.data();
  char *end = w + raw.length();
  size_t start = 0;
  while (w != end) {
    char *prev = w;
    utf8::next(w, end);
    size_t len = w - prev;
    func(start, len);
    start += len;
  }
  return start; // 返回处理的字符总数
}

}// namespace HYGUI
