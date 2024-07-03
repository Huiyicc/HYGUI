//
// Created by 19254 on 24-5-31.
//
#include <cstring>

#include "HYGUI/String.h"
//#include "include/core/SkString.h"
#include "HYGUI/Coding.h"

namespace HYGUI {
using SkString = std::string;
HYString::~HYString() {
}

HYString::HYString() {
  m_pSkString = std::make_shared<SkString>();
}

HYString::HYString(const char *pData) {
  m_pSkString = std::make_shared<SkString>(pData);
}

HYString::HYString(const wchar_t *pData) {
  auto c = W2C_(pData);
  m_pSkString = std::make_shared<SkString>(c);
  delete c;
}

HYString::HYString(const HYString &str) {
  m_pSkString = std::make_shared<SkString>(*str.m_pSkString);
}

HYString &HYString::operator=(const char *pData) {
  *m_pSkString = pData;
  return *this;
}

HYString &HYString::operator=(const std::string &str) {
  *m_pSkString = str.c_str();
  return *this;
}

HYString &HYString::operator=(const wchar_t *pData) {
  auto c = W2C_(pData);
  *m_pSkString = (c);
  delete c;
  return *this;
}

HYString &HYString::operator=(const std::wstring &str) {
  *m_pSkString = (W2C_(str.c_str()));
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

HYString &HYString::operator+=(const wchar_t *pData) {
  auto c = W2C_(pData);
  *m_pSkString += c;
  delete c;
  return *this;
}

HYString HYString::operator+(const HYString &str) {
  HYString ret;
  ret.m_pSkString = std::make_shared<SkString>(*m_pSkString);
  *ret.m_pSkString += *str.m_pSkString;
  return ret;
}

HYString HYString::operator+(const char *pData) {
  HYString ret;
  ret.m_pSkString = std::make_shared<SkString>(*m_pSkString);
  *ret.m_pSkString += pData;
  return ret;
}

HYString HYString::operator+(const wchar_t *pData) {
  HYString ret;
  ret.m_pSkString = std::make_shared<SkString>(*m_pSkString);
  *ret.m_pSkString += W2C_(pData);
  return ret;
}

bool HYString::operator==(const HYString &str) {
  return *m_pSkString == (*str.m_pSkString);
}

bool HYString::operator==(const char *pData) {
  return *m_pSkString == (pData);
}

bool HYString::operator==(const wchar_t *pData) {
  auto c = W2C_(pData);
  auto r = *m_pSkString == (c);
  delete c;
  return r;
}

bool HYString::operator!=(const HYString &str) {
  return !(*m_pSkString == (*str.m_pSkString));
}

bool HYString::operator!=(const char *pData) {
  return !(*m_pSkString == (pData));
}

bool HYString::operator!=(const wchar_t *pData) {
  auto c = W2C_(pData);
  auto r = *m_pSkString == (c);
  delete c;
  return !(r);
}

std::string_view HYString::toStdStringView() const {
  return m_pSkString->data();
}

std::string HYString::toStdString() const {
  return m_pSkString->c_str();
}

std::wstring HYString::toStdWString() const {
  return C2W_(m_pSkString->c_str());
}

HYString &HYString::operator=(const HYString &str) = default;

HYString::operator std::string() {
  return m_pSkString->c_str();
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

void HYString::append(const wchar_t *pData) {
  auto c= W2C_(pData);
  m_pSkString->append(c);
  delete c;
}

void HYString::append(const HYString &str) {
  m_pSkString->append(*str.m_pSkString);
}


}// namespace HYGUI
