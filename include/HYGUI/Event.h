//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_EVENT_H
#define HYGUI_EVENT_H

namespace HYGUI {

enum HYObjectEvent {
  HYObjectEvent_Create, // 对象创建
  HYObjectEvent_Destroy, // 对象销毁
  HYObjectEvent_Paint, // 对象重绘
};

}

#endif //HYGUI_EVENT_H
