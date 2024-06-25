//
// Created by 19254 on 24-5-31.
//
#include <cstring>

#include "HYGUI/String.h"
#include "include/core/SkString.h"
#include "HYGUI/Coding.h"

namespace HYGUI {

HYString::~HYString() {
}

HYString::HYString() {
  m_pSkString = new SkString();
}

HYString::HYString(const char *pData) {
  m_pSkString = new SkString(pData);
}

HYString::HYString(const wchar_t *pData) {
  m_pSkString = new SkString(W2C_(pData));
}

HYString::HYString(const HYString &str) {
  m_pSkString = new SkString(*str.m_pSkString);
}

HYString &HYString::operator=(const char *pData) {
  m_pSkString->set(pData);
  return *this;
}

HYString &HYString::operator=(const std::string& str) {
  m_pSkString->set(str.c_str());
  return *this;
}

HYString &HYString::operator=(const wchar_t *pData) {
  m_pSkString->set(W2C_(pData));
  return *this;
}

HYString &HYString::operator=(const std::wstring& str) {
  m_pSkString->set(W2C_(str.c_str()));
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
  *m_pSkString += W2C_(pData);
  return *this;
}

HYString HYString::operator+(const HYString &str) {
  HYString ret;
  ret.m_pSkString = new SkString(*m_pSkString);
  *ret.m_pSkString += *str.m_pSkString;
  return ret;
}

HYString HYString::operator+(const char *pData) {
  HYString ret;
  ret.m_pSkString = new SkString(*m_pSkString);
  *ret.m_pSkString += pData;
  return ret;
}

HYString HYString::operator+(const wchar_t *pData) {
  HYString ret;
  ret.m_pSkString = new SkString(*m_pSkString);
  *ret.m_pSkString += W2C_(pData);
  return ret;
}

bool HYString::operator==(const HYString &str) {
  return m_pSkString->equals(*str.m_pSkString);
}

bool HYString::operator==(const char *pData) {
  return m_pSkString->equals(pData);
}

bool HYString::operator==(const wchar_t *pData) {
  return m_pSkString->equals(W2C_(pData));
}

bool HYString::operator!=(const HYString &str) {
  return !m_pSkString->equals(*str.m_pSkString);
}

bool HYString::operator!=(const char *pData) {
  return !m_pSkString->equals(pData);
}

bool HYString::operator!=(const wchar_t *pData) {
  return !m_pSkString->equals(W2C_(pData));
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
  return m_pSkString->isEmpty();
}

void HYString::clear() {
  m_pSkString->reset();
}

size_t HYString::size() const {
  return m_pSkString->size();
}

void HYString::append(const char *pData) {
  m_pSkString->append(pData);
}

void HYString::append(const wchar_t *pData) {
  m_pSkString->append(W2C_(pData));
}

void HYString::append(const HYString &str) {
  m_pSkString->append(*str.m_pSkString);
}


}
