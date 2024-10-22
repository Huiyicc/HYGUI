//
// Created by 19254 on 24-10-21.
//

#ifndef HYGUI_HYLABEL_H
#define HYGUI_HYLABEL_H

#include <HYGUI/HYWidget.h>

namespace HYGUI {

class HYLabel : public HYWidget {
private:
  int MessageEvent(HYWidgetEvent, int64_t param1, int64_t param2) override;

public:
  HYWIDGET_BASEDEFINE_OVERRIDE(HYLabel);


};

}// namespace HYGUI

#endif//HYGUI_HYLABEL_H
