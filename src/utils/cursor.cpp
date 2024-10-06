//
// Created by 回忆 on 24-10-6.
//
#include "PrivateDefinition.h"
#include <memory>
#include <HYGUI/HYCursor.h>
#include <SDL3/SDL_mouse.h>

namespace HYGUI {

struct HYGrDirectContextPtrDeleter {
  void operator()(SDL_Cursor *ptr) const {
    if (ptr) {
      SDL_DestroyCursor(ptr);
    }
  }
};

HYGUICLASS_SRC_DEFINE(HYCursor, SDL_Cursor);

HYCursor::HYCursor()
    : m_ptr(SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(HY_SYSTEM_CURSOR_ARROW)), HYGrDirectContextPtrDeleter()) {
}

HYCursor::HYCursor(SDL_Cursor *ptr)
    : m_ptr(ptr, HYGrDirectContextPtrDeleter()) {
}

HYCursor::~HYCursor() {
  m_ptr = nullptr;
}

HYCursor& HYCursor::operator=(const nullptr_t &p) {
  m_ptr = nullptr;
  return *this;
}

HYCursor HYCursor::MakeFromSystemCursor(HY_SYSTEM_CURSOR cursor) {
  return HYCursor(SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor)));
};

}
