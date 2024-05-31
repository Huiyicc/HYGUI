//
// Created by 19254 on 24-5-31.
//
#include "HYGUI/String.h"
#include "HYGUI/Coding.h"

namespace HYGUI {

HYString::~HYString() {
}

HYString::HYString() {
  m_wstrData = L"";
  m_strData = "";
}

HYString::HYString(const char *pData) {
  auto wstr = C2W_(pData);
  m_wstrData = wstr;
  m_strData = pData;
  delete[] wstr;
}

HYString::HYString(const wchar_t *pData) {
  m_wstrData = pData;
  auto str = W2C_(pData);
  m_strData = str;
  delete[] str;
}

HYString::HYString(const HYString &str) {
  m_wstrData = str.m_wstrData;
  m_strData = str.m_strData;
}

HYString &HYString::operator=(const char *pData) {
  auto wstr = C2W_(pData);
  m_wstrData = wstr;
  m_strData = pData;
  delete[] wstr;
  return *this;
}

HYString &HYString::operator=(const std::string& str) {
  auto wstr = C2W_(str.c_str());
  m_wstrData = wstr;
  delete[] wstr;
  m_strData = str;
  return *this;
}

HYString &HYString::operator=(const wchar_t *pData) {
  m_wstrData = pData;
  auto str = W2C_(pData);
  m_strData = str;
  delete[] str;
  return *this;
}

HYString &HYString::operator=(const std::wstring& str) {
  m_wstrData = str;
  auto lstr = W2C_(str.c_str());
  m_strData = lstr;
  delete[] lstr;
  return *this;
}

HYString &HYString::operator+=(const HYString &str) {
  m_wstrData += str.m_wstrData;
  m_strData += str.m_strData;
  return *this;
}

HYString &HYString::operator+=(const char *pData) {
  auto wstr = C2W_(pData);
  m_wstrData += wstr;
  m_strData += pData;
  delete[] wstr;
  return *this;
}

HYString &HYString::operator+=(const wchar_t *pData) {
  m_wstrData += pData;
  auto str = W2C_(pData);
  m_strData += str;
  delete[] str;
  return *this;
}

HYString HYString::operator+(const HYString &str) {
  HYString ret;
  ret.m_wstrData = m_wstrData + str.m_wstrData;
  ret.m_strData = m_strData + str.m_strData;
  return ret;
}

HYString HYString::operator+(const char *pData) {
  HYString ret;
  auto wstr = C2W_(pData);
  ret.m_wstrData = m_wstrData + wstr;
  ret.m_strData = m_strData + pData;
  delete[] wstr;
  return ret;
}

HYString HYString::operator+(const wchar_t *pData) {
  HYString ret;
  ret.m_wstrData = m_wstrData + pData;
  auto str = W2C_(pData);
  ret.m_strData = m_strData + str;
  delete[] str;
  return ret;
}

bool HYString::operator==(const HYString &str) {
  return m_wstrData == str.m_wstrData;
}

bool HYString::operator==(const char *pData) {
  return (strcmp(m_strData.c_str(), pData) == 0);
}

bool HYString::operator==(const wchar_t *pData) {
  return m_wstrData == pData;
}

bool HYString::operator!=(const HYString &str) {
  return m_wstrData != str.m_wstrData;
}

bool HYString::operator!=(const char *pData) {
  return (strcmp(m_strData.c_str(), pData) != 0);
}

bool HYString::operator!=(const wchar_t *pData) {
  return m_wstrData != pData;
}

std::wstring_view HYString::toWStringView() const {
  return m_wstrData;
}

std::string_view HYString::toStringView() const {
  return m_strData;
}

std::string HYString::toStdString() const {
  return m_strData;
}

std::wstring HYString::toWString() const {
  return m_wstrData;
}

HYString &HYString::operator=(const HYString &str) = default;

HYString::operator std::string() {
  return m_strData;
}

HYString::operator std::wstring() {
  return m_wstrData;
}

bool HYString::empty() const {
  return m_wstrData.empty();
}

void HYString::clear() {
  m_wstrData.clear();
  m_strData.clear();
}

void HYString::append(const char *pData) {
  auto wstr = C2W_(pData);
  m_wstrData += wstr;
  m_strData += pData;
  delete[] wstr;
}

void HYString::append(const wchar_t *pData) {
  m_wstrData += pData;
  auto str = W2C_(pData);
  m_strData += str;
  delete[] str;
}

void HYString::append(const HYString &str) {
  m_wstrData += str.m_wstrData;
  m_strData += str.m_strData;
}


}
