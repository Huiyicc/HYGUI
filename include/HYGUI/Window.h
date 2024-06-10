//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_WINDOW_H
#define HYGUI_WINDOW_H

#include "HYGUI/Define.h"
#include "HYGUI/String.h"
#include "HYGUI/Color.h"
#include "HYGUI/Event.h"
#include "HYGUI/Object.h"

#ifdef _HOST_WINDOWS_

#include <windows.h>

#endif

namespace HYGUI {

#ifdef _HOST_WINDOWS_
constexpr int WINDOWCREATEPOINT_USEDEFAULT = CW_USEDEFAULT;
#elif defined(_HOST_APPLE_)
#include <limits>
constexpr int WINDOWCREATEPOINT_USEDEFAULT = std::numeric_limits<int>::max();
#endif

struct HYWindow;
typedef HYWindow* HYWindowHandel;

struct HYWindow {
  WINDOWHANDEL Handle = nullptr;
  VOIDPTRT OldProc = 0;
  SurfacePtr Surface = nullptr;
  CanvasPtr Canvas = nullptr;
  VOIDPTR WindowCanvasTarget = nullptr; // HDC
  VOIDPTR WindowLayeredCanvas = nullptr;
  VOIDPTR CustomBmp = nullptr;
  int Width = 0; // 窗口宽度
  int Height = 0; // 窗口高度
  int X = 0; // 窗口左上角x坐标
  int Y = 0; // 窗口左上角y坐标
  HYRect ClientRect = {0, 0, 0, 0}; // 客户区域

  int TitleBarHeight = 30; // 标题栏高度
  int BackGroundColor = 0; // 背景颜色
  int Diaphaneity = 255; // 透明度
  HYObjectEventQueue EventQueue;

  bool Drag = false; // 是否拖动
  HYPoint oldMousePoint = {0, 0}; // 旧鼠标位置
  HYPoint oldWinPoint = {0, 0}; // 旧窗口位置

  std::unordered_map<intptr_t, intptr_t> UserData; // 用户数据
  std::set<HYObject *> Children; // 组件树
};

/**
 * @brief 注册窗口类
 * @param className 窗口类名
 * @param iconPath 图标路径
 * @param cursorPath 光标路径
 * @return
 */
bool HYWindowRegisterClass(const HYString &className, const HYString &iconPath = "", const HYString &cursorPath = "");

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

/**
 * @brief 显示窗口
 * @param wnd 窗口指针
 * @return
 */
bool HYWindowShow(HYWindowHandel wnd);

/**
 * @brief 窗口消息循环
 * @param wnd 窗口指针
 * @return
 */
uint32_t HYWindowMessageLoop(HYWindowHandel wnd);

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

/**
 * @brief 挂接窗口皮肤
 * @param wnd 窗口指针
 * @param backGroundColor 背景颜色 RGB
 * @param diaphaneity 窗口透明度
 */
void HYWindowSkinHook(HYWindowHandel wnd,HYRGB backGroundColor,int diaphaneity);

/**
 * @brief 发送窗口事件
 * @param window 窗口指针
 * @param event 事件
 * @param param1 参数1
 * @param param2 参数2
 */
void HYWindowSendEvent(HYWindowHandel window, uint32_t event, intptr_t param1, intptr_t param2);

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
                                                     intptr_t value)> &callback= nullptr);

}

#endif //HYGUI_WINDOW_H
