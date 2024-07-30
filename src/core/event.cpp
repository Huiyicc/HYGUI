//
// Created by 19254 on 24-7-15.
//
#include "HYGUI/Event.h"
#include "HYGUI/EventWindow.h"


namespace HYGUI {


#define _DEF_REG_AND_UNREG_OBJECT_CALLBACK1(deftype)                                                             \
  uint32_t HYObjectEventBase::RegisterEvent##deftype##Callback(const HYObjectEvent##deftype##Handel &callback) { \
    return _registerCallback(Event##deftype##Callbacks, callback);                                               \
  }                                                                                                              \
  void HYObjectEventBase::UnRegisterEvent##deftype##Callback(uint32_t id) {                                      \
    _unRegisterCallback(Event##deftype##Callbacks, id);                                                          \
  }


_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Create);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Destroy);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Paint);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Move);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Resize);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Show);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(Hide);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(LeftDown);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(LeftUp);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(RightUp);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(RightDown);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(MiddleUp);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(MiddleDown);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(MouseMove);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(KeyDown);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(KeyUp);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(MouseWheel);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(CharInput);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(MouseEnter);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(MouseLeave);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(FocusGained);
_DEF_REG_AND_UNREG_OBJECT_CALLBACK1(FocusLost);

#define _DEF_REG_AND_UNREG_WINDOW_CALLBACK1(deftype)                                                             \
  uint32_t HYWindowEventBase::RegisterEvent##deftype##Callback(const HYWindowEvent##deftype##Handel &callback) { \
    return _registerCallback(Event##deftype##Callbacks, callback);                                               \
  };                                                                                                              \
  void HYWindowEventBase::UnRegisterEvent##deftype##Callback(uint32_t id) {                                      \
    _unRegisterCallback(Event##deftype##Callbacks, id);                                                          \
  };


_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Create);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(BackgroundPaint);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(BeforeClose);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Refresh);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(WillDestroy);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Move);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Resize);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(FirstActivate);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Tray);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Show);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(Hide);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(LeftDown);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(LeftUp);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(RightDown);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(RightUp);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(MiddleDown);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(MiddleUp);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(MouseMove);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(MouseEnter);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(MouseLeave);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(KeyDown);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(KeyUp);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(MouseWheel);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(CharInput);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(FocusGained);
_DEF_REG_AND_UNREG_WINDOW_CALLBACK1(FocusLost)


}// namespace HYGUI
