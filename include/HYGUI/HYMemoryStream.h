//
// Created by 回忆 on 24-10-4.
//

#ifndef HYMEMORYSTREAM_H
#define HYMEMORYSTREAM_H

#include <HYGUI/HYTypeDef.h>

class SkMemoryStream;

namespace HYGUI {

class HYMemoryStream : public HYClassBase {
public:
  static HYMemoryStream MakeFromData(const void *p, size_t len);

  HYMemoryStream(HYMemoryStream&& other) noexcept;

  HYMemoryStream& operator=(HYMemoryStream&& other) noexcept ;


  HYMemoryStream(const HYMemoryStream&) = delete;
  HYMemoryStream& operator=(const HYMemoryStream&) = delete;

  SkMemoryStream* get() const;
  std::unique_ptr<SkMemoryStream> release();

private:
  HYMemoryStream(const void* p, size_t len);

  std::unique_ptr<SkMemoryStream> m_ptr;
};

};

#endif //HYMEMORYSTREAM_H
