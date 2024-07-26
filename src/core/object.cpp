//
// Created by 19254 on 24-6-4.
//
#include "HYGUI/Object.h"
#include "HYGUI/Event.h"
#include "HYGUI/Utils.h"
#include "HYGUI/Keyboard.h"
#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#include <map>

namespace HYGUI {

const std::map<int, std::function<int(HYWindow *, HYObject *, HYObjectEvent, int64_t, int64_t)>> _obj_event_callback_map = {
  // 组件绘制
  {HYObjectEvent_Paint, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     for (auto &callback: obj->EventPaintCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj);
         if (r != 0) {
           break;
         }
       }
     }
     if (r == 0) {
       if (!obj->Children.empty()) {
         for (auto &child: obj->Children) {
           HYObjectPushEventCall(window, child, event, param1, param2);
         }
       }
     }
     return r;
   }},

  // 组件大小改变
  {HYObjectEvent_Resize, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     if (param1 == 0) {
       return -1;
     }
     auto rect = *(HYRect *) param1;
     delete (HYRect *) param1;
     for (auto &callback: obj->EventResizeCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, &rect);
         if (r != 0) {
           break;
         }
       }
     }
     HYObjectRefresh(obj);
     return r;
   }},

  // 组件显示
  {HYObjectEvent_Show, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     for (auto &callback: obj->EventShowCallbacks) {
       if (callback.second) {
         callback.second(window, obj);
       }
     }
     return 0;
   }},

  // 组件隐藏
  {HYObjectEvent_Hide, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     for (auto &callback: obj->EventHideCallbacks) {
       if (callback.second) {
         callback.second(window, obj);
       }
     }
     return 0;
   }},

  // 鼠标左键被按下
  {HYObjectEvent_LeftDown, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     auto mode = HYKeyboardGetMods();
     auto [x, y] = HYPointFromWParam(param2);
     for (auto &callback: obj->EventLeftDownCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, x, y, mode);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 鼠标左键被放开
  {HYObjectEvent_LeftUp, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     auto mode = HYKeyboardGetMods();
     auto [x, y] = HYPointFromWParam(param2);
     for (auto &callback: obj->EventLeftUpCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, x, y, mode);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 鼠标右键被按下
  {HYObjectEvent_RightDown, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     auto mode = HYKeyboardGetMods();
     auto [x, y] = HYPointFromWParam(param2);
     for (auto &callback: obj->EventRightDownCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, x, y, mode);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 鼠标右键被放开
  {HYObjectEvent_RightUp, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     auto mode = HYKeyboardGetMods();
     auto [x, y] = HYPointFromWParam(param2);
     for (auto &callback: obj->EventRightUpCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, x, y, mode);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 鼠标移动
  {HYObjectEvent_MouseMove, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     auto mode = HYKeyboardGetMods();
     auto [x, y] = HYPointFromWParam(param2);
     for (auto &callback: obj->EventMouseMoveCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, x, y, mode);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 鼠标进入事件
  {HYObjectEvent_MouseEnter, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     for (auto &callback: obj->EventMouseEnterCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 鼠标退出事件
  {HYObjectEvent_MouseLeave, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     for (auto &callback: obj->EventMouseLeaveCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},


  // 鼠标滚轮事件
  {HYObjectEvent_MouseWheel, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     auto mode = HYKeyboardGetMods();
     auto [x, y] = HYPointfFromWParam(param2);
     for (auto &callback: obj->EventMouseWheelCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj, x, y, mode);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},

  // 获取焦点
  {HYObjectEvent_FocusGained, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     for (auto &callback: obj->EventFocusGainedCallbacks) {
       if (callback.second) {
         callback.second(window, obj);
       }
     }
     return 0;
   }},

  // 失去焦点
  {HYObjectEvent_FocusLost, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     for (auto &callback: obj->EventFocusLostCallbacks) {
       if (callback.second) {
         callback.second(window, obj);
       }
     }
     return 0;
   }},

  // 按下某键
  {HYObjectEvent_KeyDown, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     HYKeyboardID which = HYGetHighUint32(param1);
     auto scancode = (HYScancode)HYGetLowUint32(param1);
     HYKeyCode key = HYGetHighUint32(param2);
     HYKeymod mod = HYGetLowUint32(param2);
     for (auto &callback: obj->EventKeyDownCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj,which, scancode, key, mod);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},


  // 抬起某键
  {HYObjectEvent_KeyUp, [](HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) -> int {
     int r = 0;
     HYKeyboardID which = HYGetHighUint32(param1);
     auto scancode = (HYScancode)HYGetLowUint32(param1);
     HYKeyCode key = HYGetHighUint32(param2);
     HYKeymod mod = HYGetLowUint32(param2);
     for (auto &callback: obj->EventKeyUpCallbacks) {
       if (callback.second) {
         r = callback.second(window, obj,which, scancode, key, mod);
         if (r != 0) {
           break;
         }
       }
     }
     return r;
   }},


};

int _obj_event(HYWindow *window, HYObject *obj, HYObjectEvent event, int64_t param1, int64_t param2) {
  window->LastEventObject = window->CurrentEventObject;
  window->LastEventObjectTime = window->CurrentEventObjectTime;
  window->CurrentEventObject = obj;
  window->CurrentEventObjectTime = SDL_GetTicksNS();
  if (!obj->IsShow && obj->IsVisible) {
    // 发送show消息
    obj->IsShow = true;
    HYObjectPushEventCall(window, obj, HYObjectEvent_Show, 0, 0);
  }
  int r = 0;
  if (obj->MessageEventFunc) {
    r = obj->MessageEventFunc(window, obj, event, param1, param2);
  }
  if (r != 0) {
    return r;
  }
  auto iter = _obj_event_callback_map.find(event);
  if (iter != _obj_event_callback_map.end()) {
    return iter->second(window, obj, event, param1, param2);
  }
  return 0;
}


int processing_object_event(HYObjectEventQueue *queue, HYObjectEventInfo &event_info) {
  _obj_event(event_info.Window, event_info.Object, event_info.Event, event_info.Param1, event_info.Param2);
  return 0;
}

HYObject::HYObject(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height, bool visible,
                   const HYString &className, const HYString &name, int id, HYObjectEventMessageHandel messageEventFunc)
    : Window(window), Parent(reinterpret_cast<HYObject *>(parent)), X(x), Y(y), Width(width), Height(height), IsVisible(visible),
      ClassName(std::make_shared<HYString>(className)),
      Name(std::make_shared<HYString>(name)),
      ID(id), MessageEventFunc(std::move(messageEventFunc)) {

  RawObjRect = {x, y, width, height};
  if (parent) {
    parent->Children.insert(this);
    if (x < 0) {
      VisibleRect.x = parent->VisibleRect.x;
      VisibleRect.width = x + width;

    } else {
      VisibleRect.x = parent->VisibleRect.x + x;
      VisibleRect.width = width;
    }
    if (y < 0) {
      VisibleRect.y = parent->VisibleRect.y;
      VisibleRect.height = y + height;
    } else {
      VisibleRect.y = parent->VisibleRect.y + y;
      VisibleRect.height = height;
    }
    VisibleRect.width = std::max(0, VisibleRect.width);
    VisibleRect.height = std::max(0, VisibleRect.height);
    if (VisibleRect.width > parent->Width) {
      VisibleRect.width = parent->Width;
    }
    if (VisibleRect.height > parent->Height) {
      VisibleRect.height = parent->Height;
    }
    RawObjRect.x = parent->VisibleRect.x + x;
    RawObjRect.y = parent->VisibleRect.y + y;

  } else {
    window->Children.insert(this);
    if (x < 0) {
      VisibleRect.x = 0;
      VisibleRect.width = x + width;
    } else {
      VisibleRect.x = x;
      VisibleRect.width = width;
    }
    if (y < 0) {
      VisibleRect.y = 0;
      VisibleRect.height = y + height;
    } else {
      VisibleRect.y = y;
      VisibleRect.height = height;
    }
    VisibleRect.width = std::max(0, VisibleRect.width);
    VisibleRect.height = std::max(0, VisibleRect.height);
    if (VisibleRect.width > window->Width) {
      VisibleRect.width = window->Width;
    }
    if (VisibleRect.height > window->Height) {
      VisibleRect.height = window->Height;
    }
  }
  // HYResourceRegister(ResourceType::ResourceType_Object, this, className, nullptr);
  // 创建事件
  if (MessageEventFunc) {
    MessageEventFunc(window, this, HYObjectEvent_Create, 0, 0);
  }
  for (auto &callback: EventCreateCallbacks) {
    if (callback.second) {
      callback.second(window, this);
    }
  }
}

HYObject::~HYObject() {
  if (MessageEventFunc) {
    MessageEventFunc(Window, this, HYObjectEvent_Destroy, 0, 0);
  }
  for (auto &callback: EventDestroyCallbacks) {
    if (callback.second) {
      callback.second(Window, this);
    }
  }
  for (auto &child: Children) {
    HYResourceRemove(ResourceType::ResourceType_Object, child);
  }
  Children.clear();
}

HYObjectHandle HYObjectCreate(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height, bool visible,
                              const HYString &className, const HYString &name, int id) {
  if (!window) {
    return nullptr;
  }
  if (!window->Handle.handle) {
    return nullptr;
  }
  return new HYObject{window, parent, x, y, width, height, visible, className, name, id};
}

void HYObjectPushEvent(HYWindow *window, HYObjectHandle object, HYObjectEvent event, int64_t param1, int64_t param2) {
  SDL_Event e;
  auto &l = g_app;
  e.type = g_app.EventObject;
  e.user.windowID = window->ID;
  e.user.code = (SDL_EventType) event;
  e.user.timestamp = SDL_GetTicksNS();
  auto ts = (uint64_t *) malloc(sizeof(uint64_t) * 3);
  ts[0] = uint64_t(object);
  ts[1] = param1;
  ts[2] = param2;
  e.user.data1 = ts;
  e.user.data2 = nullptr;
  SDL_PushEvent(&e);
}

void HYObjectPushEventCall(HYWindow *window, HYObjectHandle object, HYObjectEvent event, int64_t param1, int64_t param2) {
  if (!(object && window)) {
    return;
  }
  _obj_event(window, object, event, param1, param2);
}


void HYObjectRefresh(HYObjectHandle object) {
  if (!object) {
    return;
  }
  HYObjectPushEventCall(object->Window, object, HYObjectEvent_Paint, 0, 0);
}

void HYObjectDestroy(HYObjectHandle object) {
  if (object->Parent) {
    object->Parent->Children.erase(object);
  }
  HYResourceRemove(ResourceType::ResourceType_Object, object);
}

bool HYObject::contains(int px, int py) const {
  return px >= X && px < (X + Width) && py >= Y && py < (Y + Height);
}


void HYObjectUserDataAdd(HYObjectHandle object, intptr_t key, intptr_t data) {
  object->UserData[key] = data;
}

void HYObjectUserDataRemove(HYObjectHandle object, intptr_t key,
                            const std::function<bool(HYObjectHandle object, intptr_t key, intptr_t value)> &callback) {
  if (object->UserData.find(key) != object->UserData.end()) {
    if (!callback || callback(object, key, object->UserData[key])) {
      object->UserData.erase(key);
    }
  }
}

void HYObjectSetClassName(HYObjectHandle object, const HYString &className) {
  *object->ClassName = className;
}

void HYObjectSetName(HYObjectHandle object, const char *name) {
  *object->Name = name;
}

void HYObjectSetID(HYObjectHandle object, int id) {
  object->ID = id;
}


HYObjectHandle HYObjectGetFromMousePos(HYObjectHandle obj, int px, int py) {
  HYObjectHandle topObject = nullptr;
  for (auto it = obj->Children.rbegin(); it != obj->Children.rend(); ++it) {
    topObject = HYObjectGetFromMousePos(*it, px, py);
    if (topObject) {
      return topObject;
    }
  }
  // 没有子组件命中
  return HYPointIsInsideRectangle({px, py}, obj->VisibleRect) ? obj : nullptr;
}

HYObjectHandle HYObjectGetFromMousePos(HYWindowHandel window, int px, int py) {
  HYObjectHandle topObject = nullptr;
  for (auto it = window->Children.rbegin(); it != window->Children.rend(); ++it) {
    topObject = HYObjectGetFromMousePos(*it, px, py);
    if (topObject) {
      break;
    }
  }
  return topObject;
}

HYPoint HYObjectGetRelativePoint(HYObjectHandle object, int windowX, int windowY) {
  return {
    windowX - object->RawObjRect.x,
    windowY - object->RawObjRect.y};
}

HYRect HYObjectGetNestedClippedVisibleArea(HYObjectHandle object) {
  return object->VisibleRect;
}

PaintPtr HYObjectBeginPaint(HYObjectHandle object, bool clear) {
  object->Window->PaintMutex.lock();
  // 计算实际可视区域
  HYRect lct = HYObjectGetNestedClippedVisibleArea(object);
  // 创建画布
  object->Canvas = object->Window->Canvas;
  object->Canvas->save();
  //  if (object->Window->GlobalClipPath) {
  //    object->Canvas->clipPath(*object->Window->GlobalClipPath);
  //  }
  object->Canvas->clipRect(SkRect::MakeLTRB(lct.x, lct.y, lct.x + lct.width, lct.y + lct.height));
  object->Canvas->translate(object->RawObjRect.x, object->RawObjRect.y);
  // PrintDebug("HYObjectBeginPaint {} {} {} {} {}", object->Name.toStdStringView(), lct.x, lct.y, lct.width, lct.height);
  // 创建画笔
  auto repaint = new SkPaint();
  repaint->setAntiAlias(true);
  if (clear) {
    // 清除背景
    repaint->setColor(SK_ColorTRANSPARENT);
    object->Canvas->drawRect(SkRect::MakeLTRB(0, 0, object->Width, object->Height), *repaint);
    // 重置画笔
    repaint->setColor(SK_ColorBLACK);
  }
  return repaint;
}


void HYObjectEndPaint(HYObjectHandle object, SkPaint *repaint) {
  object->Canvas->restore();
  object->Canvas = nullptr;
  delete repaint;
  object->Window->PaintMutex.unlock();
}

void HYObjectResize(HYObjectHandle object, int width, int height) {
  auto rect = new HYRect{object->X, object->Y, object->Width, object->Height};
  HYObjectPushEventCall(object->Window, object, HYObjectEvent_Resize, (intptr_t) rect, 0);
}

bool HYObjectGetVisible(HYObjectHandle object) {
  return object->Visible;
}

void HYObjectSetVisible(HYObjectHandle object, bool visible, bool repaint) {
  if (visible == object->Visible) {
    if (repaint) {
      HYObjectRefresh(object);
    }
    return;
  }
  object->Visible = visible;
  if (visible) {
    HYObjectPushEventCall(object->Window, object, HYObjectEvent_Show, 0, 0);
  } else {
    HYObjectPushEventCall(object->Window, object, HYObjectEvent_Hide, 0, 0);
  }

  if (repaint) {
    HYObjectRefresh(object);
  }
}

void HYObjectSetFocus(HYObject *obj, bool focus) {
  if (!obj->AllowGetFocus) {
    // 不允许获取焦点
    return;
  }
  if (focus) {
    if (obj->Window->FocusObject == obj) {
      return;
    }
    if (obj->Window->FocusObject) {
      // 发送取消焦点事件
      HYObjectPushEventCall(obj->Window, obj->Window->FocusObject, HYObjectEvent::HYObjectEvent_FocusLost, 0, 0);
    }
    obj->Window->FocusObject = obj;
    HYObjectPushEventCall(obj->Window, obj, HYObjectEvent::HYObjectEvent_FocusGained, 0, 0);
  } else {
    if (obj->Window->FocusObject != obj) {
      return;
    }
    obj->Window->FocusObject = nullptr;
    HYObjectPushEventCall(obj->Window, obj, HYObjectEvent::HYObjectEvent_FocusLost, 0, 0);
  }


  //  if ((focus && obj->Window->FocusObject == obj)
  //      || (!focus && obj->Window->FocusObject != obj)
  //      || !obj->AllowGetFocus) {
  //    return;
  //  }
  //  auto a = HYObjectEvent::HYObjectEvent_FocusLost;
  //  auto b = HYObjectEvent::HYObjectEvent_FocusGained;
  //  if (!focus) {
  //    std::swap(a, b);
  //  }
  //  if (focus) {
  //    if (obj->Window->FocusObject) {
  //      // 如果存在
  //      // 发送取消焦点事件
  //      HYObjectPushEventCall(obj->Window, obj->Window->FocusObject, a, 0, 0);
  //    }
  //  }
  //  obj->Window->FocusObject = obj;
  //  HYObjectPushEventCall(obj->Window, obj, b, 0, 0);
}

}// namespace HYGUI
