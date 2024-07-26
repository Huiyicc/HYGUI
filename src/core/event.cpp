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


#define _DEF_REG_AND_UNREG_CALLBACK1(deftype)                                                              \
  uint32_t HYEventBase::RegisterEvent##deftype##Callback(const HYObjectEvent##deftype##Handel &callback) { \
    return _registerCallback(Event##deftype##Callbacks, callback);                                         \
  }                                                                                                        \
  void HYEventBase::UnRegisterEvent##deftype##Callback(uint32_t id) {                                      \
    _unRegisterCallback(Event##deftype##Callbacks, id);                                                    \
  }


_DEF_REG_AND_UNREG_CALLBACK1(Create);
_DEF_REG_AND_UNREG_CALLBACK1(Destroy);
_DEF_REG_AND_UNREG_CALLBACK1(Paint);
_DEF_REG_AND_UNREG_CALLBACK1(Resize);
_DEF_REG_AND_UNREG_CALLBACK1(Show);
_DEF_REG_AND_UNREG_CALLBACK1(Hide);
_DEF_REG_AND_UNREG_CALLBACK1(LeftDown);
_DEF_REG_AND_UNREG_CALLBACK1(LeftUp);
_DEF_REG_AND_UNREG_CALLBACK1(RightUp);
_DEF_REG_AND_UNREG_CALLBACK1(RightDown);
_DEF_REG_AND_UNREG_CALLBACK1(MouseMove);
_DEF_REG_AND_UNREG_CALLBACK1(KeyDown);
_DEF_REG_AND_UNREG_CALLBACK1(KeyUp);
_DEF_REG_AND_UNREG_CALLBACK1(MouseWheel);
_DEF_REG_AND_UNREG_CALLBACK1(CharInput);
_DEF_REG_AND_UNREG_CALLBACK1(MouseEnter);
_DEF_REG_AND_UNREG_CALLBACK1(MouseLeave);
_DEF_REG_AND_UNREG_CALLBACK1(FocusGained);
_DEF_REG_AND_UNREG_CALLBACK1(FocusLost);


//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventCreateCallback, HYObjectEventCreateHandel, EventCreateCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventDestroyCallback, HYObjectEventDestroyHandel, EventDestroyCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventPaintCallback, HYObjectEventPaintHandel, EventPaintCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventResizeCallback, HYObjectEventResizeHandel, EventResizeCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventShowCallback, HYObjectEventShowHandel, EventShowCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventHideCallback, HYObjectEventHideHandel, EventHideCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventLeftDownCallback, HYObjectEventLeftDownHandel, EventLeftDownCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventLeftUpCallback, HYObjectEventLeftUpHandel, EventLeftUpCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventRightUpCallback, HYObjectEventRightUpHandel, EventRightUpCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventRightDownCallback, HYObjectEventRightDownHandel, EventRightDownCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventMouseMoveCallback, HYObjectEventMouseMoveHandel, EventMouseMoveCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventKeyDownCallback, HYObjectEventKeyDownHandel, EventKeyDownCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventKeyUpCallback, HYObjectEventKeyUpHandel, EventKeyUpCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventMouseWheelCallback, HYObjectEventMouseWheelHandel, EventMouseWheelCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventCharInputCallback, HYObjectEventCharInputHandel, EventCharInputCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventMouseEnterCallback, HYObjectEventMouseEnterHandel, EventMouseEnterCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventMouseLeaveCallback, HYObjectEventMouseLeaveHandel, EventMouseLeaveCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventFocusGetCallback, HYObjectEventFocusGetHandel, EventFocusGetCallbacks);
//_DEF_REG_AND_UNREG_CALLBACK(RegisterEventFocusLostCallback, HYObjectEventFocusLostHandel, EventFocusLostCallbacks);


}// namespace HYGUI
