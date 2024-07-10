//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_WINDOW_H
#define HYGUI_WINDOW_H

#include "HYGUI/Color.h"
#include "HYGUI/Define.h"
#include "HYGUI/Event.h"
#include "HYGUI/String.h"

#ifdef _HOST_WINDOWS_

#include <windows.h>

#endif

struct SDL_Window;
struct SkPath;
struct SDL_Renderer;

namespace HYGUI {

#ifdef _HOST_WINDOWS_
constexpr int WINDOWCREATEPOINT_USEDEFAULT = CW_USEDEFAULT;
#elif defined(_HOST_APPLE_) || defined(_HOST_LINUX_)
#include <limits>
constexpr int WINDOWCREATEPOINT_USEDEFAULT = std::numeric_limits<int>::max();
#endif

struct HYWindow;
typedef HYWindow *HYWindowHandel;

class HYWindow {
public:
  virtual ~HYWindow();
  VOIDPTR GrCtx = nullptr;    // 设备上下文
  VOIDPTR SDLOpenGl = nullptr;// sdl设备上下文

  int kStencilBits = 8;// skia需要8位模板缓冲区

  uint32_t ID = 0;
  SDL_Window *SDLWindow = nullptr;
  SDL_Renderer *SDLRenderer = nullptr;
  bool IsInit = false;
  bool Show = false;
  bool isTransparent = false;

  WINDOWHANDEL Handle = nullptr;
  SurfacePtr Surface = nullptr;
  CanvasPtr Canvas = nullptr;

  bool IsReady = false;
  int Width = 0;                   // 窗口宽度
  int Height = 0;                  // 窗口高度
  int X = 0;                       // 窗口左上角x坐标
  int Y = 0;                       // 窗口左上角y坐标
  float round = 0;                    // 窗口圆角度
  float ry = 0;                    // y轴圆角半径
  HYRect ClientRect = {0, 0, 0, 0};// 客户区域
  SkPath* GlobalClipPath = nullptr;

  int TitleBarHeight = 30;// 标题栏高度
  int BackGroundColor = {0};// 背景颜色
  int Diaphaneity = 255;  // 透明度
  HYObjectEventQueue EventQueue;

  bool Drag = false;                 // 是否拖动
  int DragType = 0;                  // 拖动类型
  int DragType1 = 0;                 // 拖动类型(标记左右/上下)
  HYPoint oldMousePoint = {0, 0};    // 旧鼠标位置
  HYPoint oldMouseMovePoint = {0, 0};// 旧鼠标移动位置 (win下有可能无限触发移动事件)
  HYRect oldWinRect = {0, 0, 0, 0};  // 旧窗口位置

  std::mutex PaintMutex;                            // 绘制锁
  std::condition_variable PaintCV;                  // 绘制条件变量
  std::mutex MessageMutex;                          // 消息锁
  std::unordered_map<intptr_t, intptr_t> UserData;  // 用户数据
  std::unordered_map<intptr_t, CursorPtr> CursorMap;// 光标映射
  std::set<HYObject *> Children;                    // 组件树
};


/**
 * @brief 创建窗口
 * @param parent 父窗口
 * @param title 窗口标题
 * @param x 窗口左上角x坐标 WINDOWCREATEPOINT_
 * @param y 窗口左上角y坐标 WINDOWCREATEPOINT_
 * @param width 窗口宽度
 * @param height 窗口高度
 * @return
 */
HYWindowHandel HYWindowCreate(HYWindowHandel parent, const HYString &title,
                              int x = WINDOWCREATEPOINT_USEDEFAULT,
                              int y = WINDOWCREATEPOINT_USEDEFAULT,
                              int width = 800,
                              int height = 600);

/**
 * @brief 销毁窗口
 * @param wnd 窗口指针
 */
void HYWindowDestroy(HYWindowHandel wnd);


void* HYWindowGetHandel(HYWindowHandel wnd);

/**
 * @brief 显示窗口
 * @param wnd 窗口指针
 */
void HYWindowShow(HYWindow *wind);

uint32_t HYWindowMessageLoop();

/**
 * @brief 对话框窗口消息循环
 * @param wnd 窗口指针
 * @param parent 父窗口指针
 * @return
 */
uint32_t HYWindowMessageLoopDialog(HYWindowHandel wnd, HYWindowHandel parent = nullptr);

/**
 * @brief 窗口句柄获取窗口指针
 * @param handle 窗口句柄
 * @return
 */
HYWindowHandel HYWindowGetWindowFromHandle(WINDOWHANDEL handle);
HYWindow *HYWindowGetWindowFromID(int id);

  /**
 * @brief 挂接窗口皮肤
 * @param wnd 窗口指针
 * @param backGroundColor 背景颜色 RGB
 * @param diaphaneity 窗口透明度
 * @param round 窗口圆角半径
 */
void HYWindowSkinHook(HYWindowHandel wnd, HYRGB backGroundColor, int diaphaneity, double round=0);

/**
 * @brief 发送窗口事件
 * @param window 窗口指针
 * @param event 事件
 * @param param1 参数1,宽消息
 * @param param2 参数2,窄消息
 * @return 返回值
 */
uint64_t HYWindowSendEvent(HYWindowHandel window, uint32_t event, uint64_t param1, uint32_t param2);

/**
 * @brief 为窗口对象设置用户数据。
 *
 * 该函数用于为指定的窗口关联一组用户数据。这些数据可以是任何类型，
 * 通常用于存储与窗口相关的额外信息。
 *
 * @param window 窗口对象的句柄，将为该窗口对象设置用户数据。
 * @param key 用户数据的键，用于标识特定的用户数据。
 * @param data 用户数据值。
 */
void HYWindowUserDataAdd(HYWindowHandel window, intptr_t key, intptr_t data);

/**
 * @brief 从窗口对象获取用户数据。
 *
 * 该函数用于从指定的窗口对象中获取与指定键关联的用户数据。
 *
 * @param window 对象的句柄，用于指定窗口对象。
 * @param key 用户数据的键，用于标识特定的用户数据。
 * @param callback 回调函数，如果key存在则调用回调函数，回调为nullptr或者返回true删除数据，否则终止删除。
 */
void HYWindowUserDataRemove(HYWindowHandel window, intptr_t key,
                            const std::function<bool(HYWindowHandel window, intptr_t key,
                                                     intptr_t value)> &callback = nullptr);

void HYWindowSendEventRePaint(HYWindow *wind);


}// namespace HYGUI

#endif//HYGUI_WINDOW_H
