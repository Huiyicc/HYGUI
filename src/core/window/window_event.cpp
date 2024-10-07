//
// Created by 回忆 on 24-10-6.
//
#include "HYGUI/HYWindow.h"
#include "PrivateDefinition.h"
#include <functional>
#include <map>

namespace HYGUI {

void window_refresh(HYWindow *w, void *) {
  w->Refresh();
}

void window_create(HYWindow *window, void *) {
  if (window->m_isInit) {
    return;
  }
  // window->m_isInit = true;
  // if (window->m_show) {
  //   SDL_ShowWindow(window->m_SDLWindow);
  // }
  window->Events.Create(window);
}

void window_will_destroy(HYWindow *, void *) {
}

void window_resend_message(HYWindow *window, void *eventPtr) {
  auto event = static_cast<SDL_Event *>(eventPtr);
  int end = 0;
  SDL_Event e;
  e.window.windowID = event->user.windowID;
  e.window.timestamp = event->user.timestamp;
  e.window.reserved = event->user.reserved;
  e.window.data1 = (Sint32) (intptr_t) (event->user.data1);
  e.window.data2 = (Sint32) (intptr_t) (event->user.data2);
  if (event->user.code == HYWindowEvent::HYWindowEvent_Show) {
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
    if (event->user.code == HYWindowEvent::HYWindowEvent_Show) {
      // 第一次创建需要先显示然后重画
      SDL_ShowWindow(window->m_SDLWindow);
      HYWindowSendEventRePaint(window);
    }
  }
}

std::map<uint32_t, std::function<void(HYWindow *, void *)>> g_win_event_map = {
  {HYWindowEvent::HYWindowEvent_Refresh, window_refresh},
  {HYWindowEvent::HYWindowEvent_Create, window_create},
  {HYWindowEvent::HYWindowEvent_WillDestroy, window_will_destroy},
  {HYWindowEvent::HYWindowEvent_Show, window_resend_message},
};

int _window_event_handel(HYWindow *window, SDL_Event *event) {
  if (event->type != g_app.EventWindow) {
    if (!window->m_isInit) {
      return 0;
    }
  }
  // ---------------------窗口事件---------------------------------

  if (event->type == SDL_EventType::SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
    // 窗口将要销毁
    // handleWindowsClose(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_MOVED) {
    // 窗口移动
    // handleMove(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_LEAVE) {
    // 鼠标进入
    // handleMouseLeave(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_ENTER) {
    // 鼠标进入
    // handleMouseEnter(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_FOCUS_GAINED) {
    // 窗口获得焦点
    // handleFocusGained(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_FOCUS_LOST) {
    // 窗口失去焦点
    // handleFocusLost(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_SHOWN) {
    // 窗口显示
    // handleShown(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_HIDDEN) {
    // 窗口隐藏
    // handleHidden(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
    // 窗口大小/位置改变
    // handleSizeChanged(&event, window);
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN) {
    // 鼠标按键按下事件
    // if (handleMouseButtonDown(&event, window) != 0) {
    // continue;
    // }
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP) {
    // 鼠标按键抬起事件
    // if (handleMouseButtonUp(&event, window) != 0) {
    // continue;
    // }
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_WHEEL) {
    // 鼠标滚轮事件
    // if (handleMouseWheel(&event, window) != 0) {
    // continue;
    // }
  } else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_MOTION) {
    // 鼠标移动事件
    // if (handleMouseMotion(&event, window) != 0) {
    // continue;
    // }
  } else if (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN) {
    // 键盘按键按下事件
    // if (handleKeyDown(&event, window) != 0) {
    // continue;
    // }
  } else if (event->type == SDL_EventType::SDL_EVENT_KEY_UP) {
    // 键盘按键抬起事件
    // if (handleKeyUp(&event, window) != 0) {
    // continue;
    // }
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
    auto iter = g_win_event_map.find(event->user.code);
    if (iter != g_win_event_map.end()) {
      iter->second(window, &event->window);
    }
  } else if (event->type == g_app.EventObject) {
    // 自定义组件事件
    // auto ts = (uint64_t *) event.user.data1;
    // auto object = (HYObjectHandle) ts;
    // auto param1 = *(uint64_t *) ((uintptr_t(ts) + sizeof(uint64_t *)));
    // auto param2 = *(uint64_t *) ((uintptr_t(ts) + sizeof(uint64_t *) + sizeof(uint64_t *)));
    //   free(ts);
    //   if (object) {
    //     _obj_event(window, object, (HYObjectEvent) event.user.code, param1, param2);
    //   }
    }
  return 0;
};

}
