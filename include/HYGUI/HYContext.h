//
// Created by 回忆 on 24-10-4.
//

#ifndef HYCONTEXT_H
#define HYCONTEXT_H

#include <HYGUI/HYTypeDef.h>
#include <memory>

class GrDirectContext;

namespace HYGUI {

class HYGrDirectContext : public HYClassBase {
public:
  ~HYGrDirectContext() override;

  explicit HYGrDirectContext();
  explicit HYGrDirectContext(GrDirectContext* ptr);

  HYGUICLASS_HANDER_DEFINE(HYGrDirectContext, GrDirectContext);

  static HYGrDirectContext MakeFromDefaultInterface();
public:
  void Flush(HYSurface& surface);

};

}

#endif //HYCONTEXT_H
