//
// Created by 回忆 on 24-10-4.
//

#ifndef WINDOW_BUILDER_H
#define WINDOW_BUILDER_H

#include <HYGUI/HYTypeDef.h>
#include <HYGUI/HYWindow.h>

namespace HYGUI {

class HYWindowBuilder final : public HYClassBase {
public:
  HYWindowBuilder();

  HYWindow Build() const;
};

}

#endif //WINDOW_BUILDER_H
