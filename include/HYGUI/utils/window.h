//
// Created by 回忆 on 24-10-4.
//

#ifndef HY__WINDOW_H
#define HY__WINDOW_H

#include "./EventBase.h"
#include <HYGUI/HYCanvas.h>
#include <HYGUI/HYContext.h>
#include <HYGUI/HYDefine.h>
#include <HYGUI/HYPoint.h>
#include <HYGUI/HYRect.h>
#include <HYGUI/HYString.h>
#include <HYGUI/HYSurface.h>
#include <HYGUI/HYTypeDef.h>
#include <mutex>

union SDL_Event;

namespace HYGUI {


struct WindowHandelInfo {
#ifdef _HOST_LINUX_
  bool isWayland = false;
  /**
  * 显示字段
  * 当isWayland为true时为struct wl_display *display
  * 当isWayland为false时为Display * xdisplay (x11)
  */
  VOIDPTR handle = nullptr;
  /**
   * 保留字段
   * 当isWayland为true时为struct wl_surface * surface
   * 当isWayland为false时为Window xwindow (x11)
   */
  uintptr_t reserve = 0;
#elif defined(_HOST_WINDOWS_)
  /**
  * 窗口句柄
  */
  HWND handle = nullptr;
#elif defined(_HOST_APPLE_)
  // NSWindow*
  VOIDPTR handle = nullptr;
#endif
};


class HYWindow : public HYWindowEventBase {
public:
  [[nodiscard]] WindowHandelInfo GetHandel() const;
  ~HYWindow() override;

  uint32_t ID() const;

  void Show();

  void Refresh()const;


private:
  HYWindow();

  friend class HYWindowBuilder;
  friend int _window_event_handel(HYWindow *window, SDL_Event *event);

  void skinHook();
  void recreate_surface();

private:
  int m_id = 0;
  int m_x = WINDOWCREATEPOINT_USEDEFAULT;
  int m_y = WINDOWCREATEPOINT_USEDEFAULT;
  int m_width = 800;
  int m_height = 600;

  bool m_isInit = false;   // 是否已经初始化过
  bool m_show = false;     // 当前是否显示
  bool m_firstFocus = true;// 是否首次获取焦点

  bool m_isReady = false;// 是否已经就绪

  float round = 0;// 窗口圆角度
  float ry = 0;   // y轴圆角半径

  int m_titleBarHeight = 30;  // 标题栏高度
  int m_backGroundColor = {0};// 背景颜色
  int m_diaphaneity = 255;    // 透明度
  HYString m_title;           // 窗口标题

  bool m_drag = false;                 // 是否拖动
  int m_dragType = 0;                  // 拖动类型
  int m_dragType1 = 0;                 // 拖动类型(标记左右/上下)
  HYPoint m_oldMousePoint = {0, 0};    // 旧鼠标位置
  HYPoint m_oldMouseMovePoint = {0, 0};// 旧鼠标移动位置 (win下有可能无限触发移动事件)
  HYRect m_oldWinRect = {0, 0, 0, 0};  // 旧窗口位置

  HYRect m_ClientRect = {0};

  // HYObject *CurrentEventObject = nullptr;// 当前事件对象
  // uint64_t CurrentEventObjectTime = 0;   // 当前对象事件触发时间戳
  // HYObject *LastEventObject = nullptr;   // 上次事件对象
  // uint64_t LastEventObjectTime = 0;      // 上次事件对象触发时间戳
  // HYObject *FocusObject = nullptr;       // 当前焦点对象
  // HYObject *HoverObject = nullptr;       // 鼠标当前悬停对象

  HYGrDirectContext m_GrCtx;          // 渲染上下文
  SDL_GLContext m_SDLOpenGl = nullptr;// SDL OpenGL上下文
  SDL_Window *m_SDLWindow = nullptr;  // SDL窗口
  HYSurface m_Surface; // 窗口Surface
  HYCanvas m_Canvas; // 窗口画布

  // HYObjectEventQueue EventQueue;

  std::shared_ptr<std::mutex> m_paintMutex;                            // 绘制锁
  std::shared_ptr<std::condition_variable> m_paintCV;                  // 绘制条件变量
  std::shared_ptr<std::mutex> m_messageMutex;                          // 消息锁
  std::unordered_map<intptr_t, intptr_t> m_userData;  // 用户数据
  std::unordered_map<intptr_t, HYCursor> m_cursorMap;// 光标映射
  // std::set<HYObject *> Children;                    // 组件树
};

}// namespace HYGUI

#endif//HY__WINDOW_H
