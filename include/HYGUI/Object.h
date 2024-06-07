//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_OBJECT_H
#define HYGUI_OBJECT_H

#include <set>
#include <functional>
#include "HYGUI/Define.h"
#include "HYGUI/Event.h"

namespace HYGUI {

struct HYWindow;
struct HYObject;

typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventCallback;

typedef HYObject *HYObjectHandle;

struct HYObject {
  HYObject(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height);
  HYWindow *Window = nullptr; // 归属窗口
  HYObject *Parent = nullptr; // 父对象,为nullptr时表示为一级对象
  int X = 0; // 左上角x坐标
  int Y = 0; // 左上角y坐标
  int Width = 0; // 宽度
  int Height = 0; // 高度
  CanvasPtr Canvas = nullptr; // 画布,用于绘制,除了绘制事件外不应该直接操作
  PaintPtr Paint = nullptr; // 画笔,用于绘制,除了绘制事件外不应该直接操作
  std::set<HYObject *> Children; // 子对象
  std::vector<HYObjectEventCallback> EventCallbacks; // 事件回调
  std::unordered_map<intptr_t , void*> UserData; // 用户数据
};

/**
 * @brief 刷新对象。
 *
 * 该函数用于刷新指定的对象。
 * 底层实现为HYObjectSendEvent(window, object, HYObjectEvent_Paint, 0, 0)。
 *
 * @param object 对象的句柄，用于唯一标识对象。
 */
void HYObjectRefresh(HYObjectHandle object);

/**
 * @brief 创建对象。
 *
 * 该函数用于创建一个对象，并将其关联到指定的窗口上。
 * 对象可以是窗口内的任何元素，如按钮、文本框等。
 *
 * @param window 父窗口的指针，对象将被创建在该窗口内。
 * @param parent 父对象的句柄，如果对象没有父对象，则可以传入NULL。
 * @param x 对象在窗口内的左上角x坐标。
 * @param y 对象在窗口内的左上角y坐标。
 * @param width 对象的宽度。
 * @param height 对象的高度。
 * @return HYObjectHandle 创建的对象的句柄。
 */
HYObjectHandle HYObjectCreate(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height);

/**
 * @brief 销毁对象。
 *
 * 该函数用于销毁指定的对象，并释放与对象相关的资源。
 * 销毁对象后，应停止使用该对象的句柄。
 *
 * @param object 待销毁的对象的句柄。
 */
void HYObjectDestroy(HYObjectHandle object);

/**
 * @brief 向对象发送事件。
 *
 * 该函数用于向指定的对象发送一个事件，对象可以根据事件类型执行相应的操作。
 * 例如，点击事件可能导致对象触发一个动作或改变其状态。
 *
 * @param window 窗口的指针，事件将在这个窗口内被处理。
 * @param object 接收事件的对象的句柄。
 * @param event 发送的事件类型。
 * @param param1 事件的第一个参数，具体含义取决于事件类型。
 * @param param2 事件的第二个参数，具体含义取决于事件类型。
 */
void HYObjectSendEvent(HYWindow *window, HYObjectHandle object, int event, intptr_t param1, intptr_t param2);

/**
 * @brief 为对象添加事件回调函数。
 *
 * 该函数用于为指定的对象注册一个事件回调函数。当对象接收到特定事件时，
 * 将调用这个回调函数。
 *
 * @param object 对象的句柄，将为该对象添加事件回调。
 * @param callback 回调函数的引用，当对象接收到事件时将被调用。
 */
void HYObjectAddEventCallback(HYObjectHandle object, const HYObjectEventCallback& callback);

/**
 * @brief 为对象设置用户数据。
 *
 * 该函数用于为指定的对象关联一组用户数据。这些数据可以是任何类型，
 * 通常用于存储与对象相关的额外信息。
 *
 * @param object 对象的句柄，将为该对象设置用户数据。
 * @param key 用户数据的键，用于标识特定的用户数据。
 * @param data 用户数据的指针。
 */
void HYObjectSetUserData(HYObjectHandle object, intptr_t key, void *data);

}

#endif //HYGUI_OBJECT_H
