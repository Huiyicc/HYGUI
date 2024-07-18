//
// Created by 19254 on 24-7-15.
//
#include "HYGUI/Event.h"

namespace HYGUI {

#define _DEF_REG_AND_UNREG_CALLBACK(funcname, type, val) \
  uint32_t HYEventBase::funcname(const type &callback) { \
    return _registerCallback(val, callback);             \
  }                                                      \
  void HYEventBase::Un##funcname(uint32_t id) {          \
    _unRegisterCallback(val, id);                        \
  }

_DEF_REG_AND_UNREG_CALLBACK(RegisterEventCreateCallback, HYObjectEventCreateHandel, EventCreateCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventDestroyCallback, HYObjectEventDestroyHandel, EventDestroyCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventPaintCallback, HYObjectEventPaintHandel, EventPaintCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventResizeCallback, HYObjectEventResizeHandel, EventResizeCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventShowCallback, HYObjectEventShowHandel, EventShowCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventHideCallback, HYObjectEventHideHandel, EventHideCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventLeftDownCallback, HYObjectEventLeftDownHandel, EventLeftDownCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventLeftUpCallback, HYObjectEventLeftUpHandel, EventLeftUpCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventRightUpCallback, HYObjectEventRightUpHandel, EventRightUpCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventRightDownCallback, HYObjectEventRightDownHandel, EventRightDownCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventMouseMoveCallback, HYObjectEventMouseMoveHandel, EventMouseMoveCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventDoubleClickCallback, HYObjectEventDoubleClickHandel, EventDoubleClickCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventKeyDownCallback, HYObjectEventKeyDownHandel, EventKeyDownCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventKeyUpCallback, HYObjectEventKeyUpHandel, EventKeyUpCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventMouseWheelCallback, HYObjectEventMouseWheelHandel, EventMouseWheelCallbacks);
_DEF_REG_AND_UNREG_CALLBACK(RegisterEventCharInputCallback, HYObjectEventCharInputHandel, EventCharInputCallbacks);


}// namespace HYGUI
