//
// Created by 回忆 on 24-10-4.
//

#ifndef HYWINDOW_H
#define HYWINDOW_H

#include "./utils/window.h"
#include "./utils/window_builder.h"

namespace HYGUI {

HYWindow* HYWindowGetFromID(uint32_t id);

void HYWindowSendEventRePaint(const HYWindow *wind);

uint64_t HYWindowSendEvent(const HYWindow * wind, HYWindowEvent event, uint64_t data1, uint64_t data2);

};

#endif //HYWINDOW_H
