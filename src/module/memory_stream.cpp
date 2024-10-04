//
// Created by 回忆 on 24-10-4.
//
#include "PrivateDefinition.h"
#include <HYGUI/HYMemoryStream.h>
#include "include/core/SkStream.h"

namespace HYGUI {

HYMemoryStream::HYMemoryStream(const void *p, size_t len)
    : m_ptr(SkMemoryStream::MakeDirect(p, len)) {
}

HYMemoryStream HYMemoryStream::MakeFromData(const void *p, size_t len) {
  return {p, len};
};

HYMemoryStream::HYMemoryStream(HYMemoryStream&& other) noexcept
          : m_ptr(std::move(other.m_ptr)) {
}

HYMemoryStream& HYMemoryStream::operator=(HYMemoryStream&& other) noexcept {
  if (this != &other) {
    m_ptr = std::move(other.m_ptr);
  }
  return *this;
}

std::unique_ptr<SkMemoryStream> HYMemoryStream::release() {
  return std::move(m_ptr);
}

SkMemoryStream* HYMemoryStream::get() const {
  return m_ptr.get();
};

}

