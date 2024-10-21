//
// Created by 回忆 on 24-10-6.
//
#include "HYGUI/HYMouse.h"
#include "HYGUI/HYPaint.h"
#include "HYGUI/HYWidget.h"
#include "HYGUI/HYWindow.h"
#include "PrivateDefinition.h"
#include <functional>
#include <map>

namespace HYGUI {

extern std::map<HYWindowEvent, std::function<void(HYWindow *, void *)>> g_win_event_map;


void HYWindowHelpers::window_create(HYWindow *window, void *) {
  if (window->m_isInit) {
    return;
  }
  // window->m_isInit = true;
  // if (window->m_show) {
  //   SDL_ShowWindow(window->m_SDLWindow);
  // }
  window->Events.OnCreate(window);
}

void HYWindowHelpers::window_will_destroy(HYWindow *, void *) {
}

void HYWindowHelpers::window_resend_message(HYWindow *window, void *eventPtr) {
  auto event = static_cast<SDL_Event *>(eventPtr);
  int end = 0;
  SDL_Event e;
  e.window.windowID = event->user.windowID;
  e.window.timestamp = event->user.timestamp;
  e.window.reserved = event->user.reserved;
  e.window.data1 = (Sint32) (intptr_t) (event->user.data1);
  e.window.data2 = (Sint32) (intptr_t) (event->user.data2);
  if (event->user.code == (uint32_t) HYWindowEvent::HYWindowEvent_Show) {
    e.type = SDL_EVENT_WINDOW_SHOWN;
    if (!window->m_isInit) {
      // 窗口刚创建的时候会有一个show事件，需要初始化
      window->m_isInit = true;
      // 窗口第一次show
      end = 1;
    }
  }
  SDL_PushEvent(&e);
  if (end != 0) {
    if (event->user.code == (uint32_t) HYWindowEvent::HYWindowEvent_Show) {
      // 第一次创建需要先显示然后重画
      SDL_ShowWindow(window->m_SDLWindow);
      HYWindowSendEventRePaint(window);
    }
  }
}


void HYWindowHelpers::window_refresh(HYWindow *w, void *) {
  // 切换到OpenGL上下文
  SDL_GL_MakeCurrent(w->m_SDLWindow, w->m_SDLOpenGl);

  w->m_canvas = w->m_surface.GetCanvas();
  // 透明背景
  if (w->m_round > 0) {
    // 圆角
    w->m_canvas.ClipRRect({0, 0, static_cast<float>(w->m_width), static_cast<float>(w->m_height), w->m_round, w->m_round});
  }

  HYPaint bgpaint;
  bgpaint.SetARGB(HYColorRGBToARGB(w->m_backGroundColor, 255));
  // 白色
  bgpaint.SetAntiAlias(true);
  w->m_canvas.DrawRect(bgpaint, {0, 0, w->m_clientRect.width, w->m_clientRect.height});
  HYRect bgpaint_rect = {0, 0, w->m_width, w->m_height};
  w->Events.OnBackgroundPaint(w, &w->m_canvas, &bgpaint, &bgpaint_rect);

  // 子组件绘制
  w->m_canvas.Save();
  for (auto widget: w->m_children) {
    _widget_call_(w,widget, HYWidgetEvent::HYWidgetEvent_Paint, 0, 1);
  }

  w->m_canvas.Restore();
  w->m_canvas.ResetMatrix();

  w->m_GrCtx.Flush(w->m_surface);

  // 将绘制的内容显示到窗口
  SDL_GL_SwapWindow(w->m_SDLWindow);
}

int HYWindowHelpers::getMouseCursorType(HYWindow *window, int x, int y, int edge) {
  int dragType = HY_SYSTEM_CURSOR_ARROW;
  if (x <= edge) {
    if (y <= edge) {
      // 左上角
      dragType = HY_SYSTEM_CURSOR_SIZENWSE;
    } else if (y >= window->Height() - edge) {
      // 左下角
      dragType = HY_SYSTEM_CURSOR_SIZENESW;
    } else {
      // 左边缘
      dragType = HY_SYSTEM_CURSOR_SIZEWE;
    }
  } else if (x >= window->Width() - edge) {
    if (y <= edge) {
      // 右上角
      dragType = HY_SYSTEM_CURSOR_SIZENESW;
      window->m_dragType1 = 1;
    } else if (y >= window->Height() - edge) {
      // 右下角
      dragType = HY_SYSTEM_CURSOR_SIZENWSE;
      window->m_dragType1 = 1;
    } else {
      // 右边缘
      dragType = HY_SYSTEM_CURSOR_SIZEWE;
      window->m_dragType1 = 1;
    }
  } else if (y <= edge) {
    // 上边缘
    dragType = HY_SYSTEM_CURSOR_SIZENS;
  } else if (y >= window->Height() - edge) {
    // 下边缘
    dragType = HY_SYSTEM_CURSOR_SIZENS;
    window->m_dragType1 = 1;
  } else {
    // 恢复默认
    dragType = HY_SYSTEM_CURSOR_ARROW;
    window->m_dragType1 = 0;
  }
  return dragType;
}


int HYWindowHelpers::handleWindowsClose(SDL_Event *event, HYWindow *window) {
  std::lock_guard<std::mutex> lock_table(g_app.WindowsTableMutex);
  window->Events.OnBeforeClose(window);
  for (auto iter = g_app.WindowsTable.begin(); iter != g_app.WindowsTable.end();) {
    if (iter->get() == window) {
      // HYResourceRemove(ResourceType::ResourceType_Window, window);
      SDL_DestroyWindow(window->SDLWindow());
      g_app.WindowsTable.erase(iter);
      break;
    } else {
      ++iter;
    }
  }
  return 0;
}

int HYWindowHelpers::handleMouseButtonDown(SDL_Event *event, HYWindow *window) {
  // 鼠标按键按下事件
  //    auto push_event = HYObjectEvent::HYObjectEvent_LeftDown;
  HYEventRegistry<std::function<void(HYGUI::HYWindow *, int, int, HYGUI::HYKeymod)>, void (*)(HYWindow *, int, int, HYKeymod)> *spr = nullptr;
  if (event->button.button == SDL_BUTTON_LEFT) {
    // 左键被按下
    //        push_event = HYObjectEvent::HYObjectEvent_LeftDown;
    spr = &window->Events.OnLeftClickStart;
  } else if (event->button.button == SDL_BUTTON_RIGHT) {
    // 右键被按下
    //    push_event = HYObjectEvent::HYObjectEvent_RightDown;
    spr = &window->Events.OnRightClickStart;
  } else if (event->button.button == SDL_BUTTON_MIDDLE) {
    // 中键被按下
    //    push_event = HYObjectEvent::HYObjectEvent_MiddleDown;
    spr = &window->Events.OnMiddleClickStart;
  }
  auto dragType = getMouseCursorType(window, event->button.x, event->button.y);
  if ((event->button.y < window->m_titleBarHeight && event->button.y > 0) || dragType != HY_SYSTEM_CURSOR_ARROW) {
    // 准备移动窗口
    window->m_drag = true;
    window->m_dragType = dragType == HY_SYSTEM_CURSOR_ARROW ? 0 : dragType;
    auto wp = HYMouseGetPosition();
    window->m_oldMousePoint = {int(wp.x), int(wp.y)};
    window->m_oldWinRect = {window->X(), window->Y(), window->Width(), window->Height()};

    //      window->m_LastEventObject = window->CurrentEventObject;
    //      window->LastEventObjectTime = window->CurrentEventObjectTime;
    //      window->CurrentEventObject = nullptr;
    //      window->CurrentEventObjectTime = event->button.timestamp;
  } else {
    // 通知子组件
    window->m_drag = false;
    window->m_dragType = 0;
    //      auto act_obj = HYObjectGetFromMousePos(window, event->button.x, event->button.y);
    //      if (act_obj) {
    //        if (push_event == HYObjectEvent::HYObjectEvent_LeftDown) {
    //          // 组件获取焦点
    //          HYObjectSetFocus(act_obj, true);
    //        }
    //        // 转换坐标
    //        auto [x1, y1] = HYObjectGetRelativePoint(act_obj, event->button.x, event->button.y);
    //        HYObjectPushEventCall(window, act_obj, push_event, 0, HYPointGenWParam(x1, y1));
    //      } else {
    //            if (window->FocusObject) {
    //              // 组件释放焦点
    //              HYObjectSetFocus(window->FocusObject, false);
    //            }
    // 为窗口
    if (spr) {
      auto p = HYMouseGetPositionFromWindow(window);
      auto mod = HYKeyboardGetMods();
      (*spr)(window, static_cast<int>(p.x), static_cast<int>(p.y), mod);
    }
    //      }
  }
  return 0;
}

int HYWindowHelpers::handleMouseButtonUp(SDL_Event *event, HYWindow *window) {
  // 鼠标按键放开
  //  auto push_event = HYObjectEvent::HYObjectEvent_LeftUp;
  HYEventRegistry<std::function<void(HYGUI::HYWindow *, int, int, HYGUI::HYKeymod)>, void (*)(HYWindow *, int, int, HYKeymod)> *spr = nullptr;
  if (event->button.button == SDL_BUTTON_LEFT) {
    // 左键被放开
    //      push_event = HYObjectEvent::HYObjectEvent_LeftUp;
    spr = &window->Events.OnLeftClickEnd;
  } else if (event->button.button == SDL_BUTTON_RIGHT) {
    // 右键被放开
    //      push_event = HYObjectEvent::HYObjectEvent_RightUp;
    spr = &window->Events.OnRightClickEnd;
  } else if (event->button.button == SDL_BUTTON_MIDDLE) {
    // 中键被放开
    //      push_event = HYObjectEvent::HYObjectEvent_MiddleUp;
    spr = &window->Events.OnRightClickEnd;
  }
  auto dragType = getMouseCursorType(window, event->button.x, event->button.y);
  if ((event->button.y < window->m_titleBarHeight && event->button.y > 0) || dragType != HY_SYSTEM_CURSOR_ARROW) {
    // 准备移动窗口
    window->m_drag = false;
    window->m_dragType = 0;
    window->m_oldWinRect = {0, 0, 0, 0};
    window->m_oldMousePoint = {0, 0};
  } else {
    // 通知子组件
    window->m_drag = false;
    window->m_dragType = 0;
    window->m_oldWinRect = {0, 0, 0, 0};
    window->m_oldMousePoint = {0, 0};
    //    auto act_obj = HYObjectGetFromMousePos(window, event->button.x, event->button.y);
    //    if (act_obj) {
    //      // 转换坐标
    //      auto [x1, y1] = HYObjectGetRelativePoint(act_obj, event->button.x, event->button.y);
    //      HYObjectPushEventCall(window, act_obj, push_event, 0, HYPointGenWParam(x1, y1));
    //    }
    //    // 为窗口
    //    if (spr) {
    if (spr) {
      auto p = HYMouseGetPositionFromWindow(window);
      auto mod = HYKeyboardGetMods();
      (*spr)(window, static_cast<int>(p.x), static_cast<int>(p.y), mod);
    }

    //    }
  }
  return 0;
}

int HYWindowHelpers::handleMouseMotion(SDL_Event *event, HYWindow *window) {
  // 鼠标移动事件
  if (window->m_drag) {
    if (window->m_dragType == 0) {
      // 移动窗口
      auto wp = HYMouseGetPosition();
      window->m_x = window->m_oldWinRect.x + wp.x - window->m_oldMousePoint.x;
      window->m_y = window->m_oldWinRect.y + wp.y - window->m_oldMousePoint.y;
      SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
      //      HYPoint newPorint{window->m_x, window->m_y};
      //      window->Events.OnMove(window, &newPorint);
    } else if (window->m_dragType == HY_SYSTEM_CURSOR_SIZENWSE) {
      // 处于左上/右下角调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->m_dragType1 == 0) {
        // 左上角
        window->m_x = window->m_oldWinRect.x + wp.x - window->m_oldMousePoint.x;
        window->m_y = window->m_oldWinRect.y + wp.y - window->m_oldMousePoint.y;
        window->m_width = window->m_oldWinRect.width + window->m_oldWinRect.x - window->m_x;
        window->m_height = window->m_oldWinRect.height + window->m_oldWinRect.y - window->m_y;
        SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      } else {
        // 右下角
        window->m_width = window->m_oldWinRect.width + wp.x - window->m_oldMousePoint.x;
        window->m_height = window->m_oldWinRect.height + wp.y - window->m_oldMousePoint.y;
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      }
    } else if (window->m_dragType == HY_SYSTEM_CURSOR_SIZENESW) {
      // 处于左下/右上角调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->m_dragType1 == 0) {
        // 左下角
        window->m_x = window->m_oldWinRect.x + wp.x - window->m_oldMousePoint.x;
        window->m_width = window->m_oldWinRect.width + window->m_oldWinRect.x - window->m_x;
        window->m_height = window->m_oldWinRect.height + wp.y - window->m_oldMousePoint.y;
        SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      } else {
        // 右上角
        window->m_y = window->m_oldWinRect.y + wp.y - window->m_oldMousePoint.y;
        window->m_width = window->m_oldWinRect.width + wp.x - window->m_oldMousePoint.x;
        window->m_height = window->m_oldWinRect.height + window->m_oldWinRect.y - window->m_y;
        SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      }
    } else if (window->m_dragType == HY_SYSTEM_CURSOR_SIZEWE) {
      // 处于左右边缘调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->m_dragType1 == 0) {
        // 左边缘
        window->m_x = window->m_oldWinRect.x + wp.x - window->m_oldMousePoint.x;
        window->m_width = window->m_oldWinRect.width + window->m_oldWinRect.x - window->m_x;
        SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      } else {
        // 右边缘
        window->m_width = window->m_oldWinRect.width + wp.x - window->m_oldMousePoint.x;
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      }
    } else if (window->m_dragType == HY_SYSTEM_CURSOR_SIZENS) {
      // 处于上下边缘调整窗口尺寸
      auto wp = HYMouseGetPosition();
      if (window->m_dragType1 == 0) {
        // 上边缘
        window->m_y = window->m_oldWinRect.y + wp.y - window->m_oldMousePoint.y;
        window->m_height = window->m_oldWinRect.height + window->m_oldWinRect.y - window->m_y;
        SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      } else {
        // 下边缘
        window->m_height = window->m_oldWinRect.height + wp.y - window->m_oldMousePoint.y;
        SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
      }
    } else if (window->m_dragType == HY_SYSTEM_CURSOR_SIZENWSE) {
      // 处于左下角调整窗口尺寸
      auto wp = HYMouseGetPosition();
      window->m_x = window->m_oldWinRect.x + wp.x - window->m_oldMousePoint.x;
      window->m_width = window->m_oldWinRect.width + window->m_oldWinRect.x - window->m_x;
      window->m_height = window->m_oldWinRect.height + window->m_oldWinRect.y - window->m_y;
      SDL_SetWindowPosition(window->m_SDLWindow, window->m_x, window->m_y);
      SDL_SetWindowSize(window->m_SDLWindow, window->m_width, window->m_height);
    } else {
      return 1;
    }
    //    HYRect newRect{window->m_x, window->m_y, window->m_width, window->m_height};
    //    window->Events.OnResize(window, &newRect);
    return 1;
  } else {
    int x = event->motion.x;
    int y = event->motion.y;
    auto dragType = getMouseCursorType(window, x, y);
    SDL_SetCursor(window->m_cursorMap[dragType].get());
    window->m_dragType = dragType;

    //        auto obj = HYObjectGetFromMousePos(window, event->button.x, event->button.y);
    //    if (obj) {
    //      if (window->CurrentEventObject != obj) {
    //        if (window->CurrentEventObject) {
    //          // 退出事件
    //          HYObjectPushEventCall(window, window->CurrentEventObject, HYObjectEvent::HYObjectEvent_MouseLeave, 0, 0);
    //        }
    //        window->HoverObject = obj;
    //        // 进入事件
    //        HYObjectPushEventCall(window, obj, HYObjectEvent::HYObjectEvent_MouseEnter, 0, 0);
    //      }
    //      // 转换坐标
    //      auto [x1, y1] = HYObjectGetRelativePoint(obj, event->button.x, event->button.y);
    //      HYObjectPushEventCall(window, obj, HYObjectEvent_MouseMove, 0, HYPointGenWParam(x1, y1));
    //    } else {
    //          if (window->CurrentEventObject && window->HoverObject) {
    //            // 退出事件
    //            auto hoverObj = window->HoverObject;
    //            window->HoverObject = nullptr;
    //            HYObjectPushEventCall(window, hoverObj, HYObjectEvent::HYObjectEvent_MouseLeave, 0, 0);
    //            window->LastEventObject = window->CurrentEventObject;
    //            window->LastEventObjectTime = window->CurrentEventObjectTime;
    //            window->CurrentEventObject = nullptr;
    //            window->CurrentEventObjectTime = SDL_GetTicksNS();
    //          }
    auto p = HYMouseGetPositionFromWindow(window);
    auto mod = HYKeyboardGetMods();
    window->Events.OnMouseMove(window, static_cast<int>(p.x), static_cast<int>(p.y), mod);

    //    }
  }
  return 0;
}

int HYWindowHelpers::handleFocusGained(SDL_Event *event, HYWindow *window) {
  if (window->m_firstFocus) {
    // 首次激活
    window->m_firstFocus = false;
    window->Events.OnFirstActivate(window);
  }
  window->m_focusStatus = true;
  window->Events.OnFocusGained(window);
  return 0;
}

int HYWindowHelpers::handleFocusLost(SDL_Event *event, HYWindow *window) {
  window->m_focusStatus = false;
  window->Events.OnFocusLost(window);
  return 0;
}

int HYWindowHelpers::handleShown(SDL_Event *event, HYWindow *window) {
  window->m_show = true;
  window->Events.OnShown(window);
  return 0;
}

int HYWindowHelpers::handleHidden(SDL_Event *event, HYWindow *window) {
  window->m_show = false;
  window->Events.OnHidden(window);
  return 0;
}

int HYWindowHelpers::handleMove(SDL_Event *event, HYWindow *window) {
  window->m_x = event->window.data1;
  window->m_y = event->window.data2;
  HYPoint pNew{event->window.data1, event->window.data2};
  window->Events.OnMove(window, &pNew);
  return 0;
}

int HYWindowHelpers::handleSizeChanged(SDL_Event *event, HYWindow *window) {
  window->m_width = event->window.data1;
  window->m_height = event->window.data2;
  HYRect nRect{window->m_x, window->m_y, window->m_width, window->m_height};
  window->Events.OnResize(window, &nRect);
  HYWindowSendEventRePaint(window);
  return 0;
}

int HYWindowHelpers::handleKeyDown(SDL_Event *event, HYWindow *window) {
//  if (!window->FocusObject) {
    // 窗口
    window->Events.OnKeyPress(window,
                              static_cast<HYKeyboardID>(event->key.which),
                              static_cast<HYScancode>(event->key.scancode),
                              static_cast<HYKeyCode>(event->key.key),
                              static_cast<HYKeymod>(event->key.mod));
//  } else {
//    auto p1 = HYCombineUint32(event->key.which, event->key.scancode);
//    auto p2 = HYCombineUint32(event->key.key, event->key.mod);
//    HYObjectPushEventCall(window, window->FocusObject, HYObjectEvent_KeyDown, p1, p2);
//  }
  return 0;
}

int HYWindowHelpers::handleKeyUp(SDL_Event *event, HYWindow *window) {
//  if (!window->FocusObject) {
    // 窗口
    window->Events.OnKeyRelease(window,
                                static_cast<HYKeyboardID>(event->key.which),
                                static_cast<HYScancode>(event->key.scancode),
                                static_cast<HYKeyCode>(event->key.key),
                                static_cast<HYKeymod>(event->key.mod));
//  } else {
//    auto p1 = HYCombineUint32(event->key.which, event->key.scancode);
//    auto p2 = HYCombineUint32(event->key.key, event->key.mod);
//    HYObjectPushEventCall(window, window->FocusObject, HYObjectEvent_KeyUp, p1, p2);
//  }
  return 0;
}

int HYWindowHelpers::handleMouseWheel(SDL_Event *event, HYWindow *window) {
  // 屏幕坐标转窗口坐标
  // auto [bx, by] = HYMouseGetPositionFromWindow(window);
//  auto obj = HYObjectGetFromMousePos(window, bx, by);
//  if (obj) {
//    auto lp = HYPointfGenWParam(event->wheel.x, event->wheel.y);
//    HYObjectPushEventCall(window, obj, HYObjectEvent::HYObjectEvent_MouseWheel, 0, lp);
//  } else {
    // 窗口
    auto mod = HYKeyboardGetMods();
    window->Events.OnMouseScroll(window, event->wheel.x, event->wheel.y, mod);
//  }
  return 0;
}

int HYWindowHelpers::_window_event_handel(HYWindow *window, SDL_Event *event) {
  if (event->type != g_app.EventWindow) {
    if (!window->m_isInit) {
      return 0;
    }
  }
  // ---------------------窗口事件---------------------------------

  if (event->type == SDL_EventType::SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
    // 窗口将要销毁
    handleWindowsClose(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_MOVED) {
    // 窗口移动
    handleMove(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_LEAVE) {
    // 鼠标进入
    // handleMouseLeave(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_ENTER) {
    // 鼠标进入
    // handleMouseEnter(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_FOCUS_GAINED) {
    // 窗口获得焦点
    handleFocusGained(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_FOCUS_LOST) {
    // 窗口失去焦点
    handleFocusLost(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_SHOWN) {
    // 窗口显示
    handleShown(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_HIDDEN) {
    // 窗口隐藏
    handleHidden(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
    // 窗口大小/位置改变
    handleSizeChanged(event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN) {
    // 鼠标按键按下事件
    if (handleMouseButtonDown(event, window) != 0) {
      return 0;
    }
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP) {
    // 鼠标按键抬起事件
    if (handleMouseButtonUp(event, window) != 0) {
      return 0;
    }
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_WHEEL) {
    // 鼠标滚轮事件
    if (handleMouseWheel(event, window) != 0) {
      return 0;
    }
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_MOTION) {
    // 鼠标移动事件
    if (handleMouseMotion(event, window) != 0) {
      return 0;
    }
  } else if (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN) {
    // 键盘按键按下事件
     if (handleKeyDown(event, window) != 0) {
       return 0;
     }
  } else if (event->type == SDL_EventType::SDL_EVENT_KEY_UP) {
    // 键盘按键抬起事件
     if (handleKeyUp(event, window) != 0) {
       return 0;
     }
  } else if (event->type == SDL_EventType::SDL_EVENT_TEXT_INPUT) {
    // 输入文本
    // if (handleTextInput(&event, window) != 0) {
    // continue;
    // }
  } else if (event->type == SDL_EventType::SDL_EVENT_TEXT_EDITING) {
    // 输入文本
  } else if (event->type == SDL_EventType::SDL_EVENT_TEXT_EDITING_CANDIDATES) {
    // 输入候选词
  } else if (event->type == g_app.EventWindow) {
    // 自定义窗口事件
    auto iter = g_win_event_map.find((HYWindowEvent) event->user.code);
    if (iter != g_win_event_map.end()) {
      iter->second(window, &event->window);
    }
  } else if (event->type == g_app.EventObject) {
    // 自定义组件事件
    auto ts = (uint64_t *) event->user.data1;
    if (!ts) {
      return 0;
    }
    auto object = (HYWidget *) ts;
    DEFER(free(ts));
    auto param1 = *(uint64_t *) ((uintptr_t(ts) + sizeof(uint64_t *)));
    auto param2 = *(uint64_t *) ((uintptr_t(ts) + sizeof(uint64_t *) + sizeof(uint64_t *)));
    if (object) {
      _widget_call_(window, object, (HYWidgetEvent) event->user.code, param1, param2);
    }
  }
  return 0;
};


std::map<HYWindowEvent, std::function<void(HYWindow *, void *)>> g_win_event_map = {
  {HYWindowEvent::HYWindowEvent_Refresh, HYWindowHelpers::window_refresh},
  {HYWindowEvent::HYWindowEvent_Create, HYWindowHelpers::window_create},
  {HYWindowEvent::HYWindowEvent_WillDestroy, HYWindowHelpers::window_will_destroy},
  {HYWindowEvent::HYWindowEvent_Show, HYWindowHelpers::window_resend_message},
};

}// namespace HYGUI
