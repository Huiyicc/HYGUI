//
// Created by 回忆 on 24-10-6.
//
#include <PrivateDefinition.h>
#include <HYGUI/HYWindow.h>

namespace  HYGUI {

HYWindow* HYWindowGetFromID(const uint32_t id) {
  std::lock_guard<std::mutex> lock(g_app.WindowsTableMutex);
  auto &debug_app = g_app;
  if (!g_app.WindowsTable.empty()) {
    for (auto &iter: g_app.WindowsTable) {
      if (iter->ID() == id) {
        return iter;
      }
    }
  }

  return nullptr;
};

void HYWindowSendEventRePaint(const HYWindow *wind) {
  SDL_Event event;
  event.type = g_app.EventWindow;
  event.user.windowID = wind->ID();
  event.user.code = HYWindowEvent_Refresh;
  event.user.data1 = nullptr;
  event.user.data2 = nullptr;
  SDL_PushEvent(&event);
}

uint64_t HYWindowSendEvent(const HYWindow * wind, HYWindowEvent event, uint64_t data1, uint64_t data2) {
  SDL_Event e;
  e.type = g_app.EventWindow;
  e.user.code = event;
  e.user.windowID = wind->ID();
  e.user.timestamp = SDL_GetTicksNS();
  e.user.data1 = (void *) data1;
  e.user.data2 = (void *) data2;
  return SDL_PushEvent(&e);
  //  e.window.windowID = wind->ID;
  //  e.window.reserved = HYWindowEvent_Paint;
  //  e.window.data1 = 0;
  //  e.window.data2 = 0;
  //  SDL_PushEvent(&event);
}

}