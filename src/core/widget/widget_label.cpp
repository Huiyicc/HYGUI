//
// Created by 19254 on 24-10-21.
//
#include "PrivateDefinition.h"
#include <HYGUI/Widgets/HYLabel.h>

namespace HYGUI {

int HYLabel::MessageEvent(HYWidgetEvent event, int64_t param1, int64_t param2) {
  PrintDebug("msg:{}",(int32_t )event);
  return 0;
}

}// namespace HYGUI