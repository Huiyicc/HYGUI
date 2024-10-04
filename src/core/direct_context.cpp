//
// Created by 回忆 on 24-10-4.
//
#include <HYGUI/HYContext.h>
#include <PrivateDefinition.h>
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include <gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLAssembleInterface.h>

namespace HYGUI {

GrGLFuncPtr glgetpoc(void *ctx, const char name[]) {
  return (GrGLFuncPtr) SDL_GL_GetProcAddress(name);
}

HYGUICLASS_SRC_DEFINE(HYGrDirectContext, GrDirectContext);

// bool HYGrDirectContext::operator==(const nullptr_t &p) const { return m_ptr == p; }
// GrDirectContext *HYGrDirectContext::operator->() const { return m_ptr.get(); };
// GrDirectContext *HYGrDirectContext::get() const { return m_ptr.get(); };
// bool HYGrDirectContext::operator!() const { return !m_ptr; };

HYGrDirectContext::HYGrDirectContext() {

}


struct HYGrDirectContextPtrDeleter {
  void operator()(GrDirectContext *ptr) const {
    if (ptr) {
      ptr->abandonContext();
      ptr->unref();
    }
  }
};

HYGrDirectContext::HYGrDirectContext(GrDirectContext *ptr)
    : m_ptr(ptr, HYGrDirectContextPtrDeleter()) {
};

HYGrDirectContext::~HYGrDirectContext() {

};

HYGrDirectContext HYGrDirectContext::MakeFromDefaultInterface() {
  auto skInterface = GrGLMakeNativeInterface();
  if (!skInterface) {
    skInterface = GrGLMakeAssembledInterface(
      nullptr, glgetpoc);
    if (!skInterface) {
        return HYGrDirectContext(nullptr);
    }
  }
  sk_sp<GrDirectContext> grContext(GrDirectContexts::MakeGL(skInterface));
  return HYGrDirectContext(grContext.release());
};

}