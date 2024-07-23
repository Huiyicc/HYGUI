//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_OBJECT_H
#define HYGUI_OBJECT_H

#include "HYGUI/Define.h"
#include "HYGUI/Event.h"
#include "HYGUI/TypeDef.h"
#include <functional>
#include <set>

namespace HYGUI {

class HYWindow;
class HYObject;

typedef std::function<int(HYWindow *, HYObject *, int, int, int)> HYObjectEventCallback;

class HYObjectBase : public HYEventBase {
public:
  ~HYObjectBase() override = default;
};

/**
 * 定义HYLabel的指针类型，作为标签控件的句柄。
 */
typedef HYObject *HYObjectHandle;

/**
 * 定义HYLabel类，继承自HYObject，用于创建和管理标签控件。
 * 标签控件用于显示文本信息，并可设置背景色。
 */
class HYObject : public HYObjectBase {

public:
  HYObject(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height,bool visible, const HYString &className,
           const HYString &name = "", int id = 0, HYObjectEventMessageHandel messageEventFunc = nullptr);
  ~HYObject() override;

  bool IsShow = false;
  bool IsVisible = false;

  HYWindow *Window = nullptr;// 归属窗口
  HYObject *Parent = nullptr;// 父对象,为nullptr时表示为一级对象

  int X = 0;     // 左上角x坐标
  int Y = 0;     // 左上角y坐标
  int Width = 0; // 宽度
  int Height = 0;// 高度
  bool Visible = false;

  HYRect VisibleRect = {0};// 相对于窗口的实际可视范围
  HYRect RawObjRect = {0}; // 相对于窗口的实际范围(无裁剪)

  std::shared_ptr<HYString> ClassName;// 组件类名
  std::shared_ptr<HYString> Name;     // 组件名
  int ID = 0;                         // 组件ID

  HYObjectEventMessageHandel MessageEventFunc = nullptr; // 用户消息事件回调

  CanvasPtr Canvas = nullptr;                     // 画布,用于绘制,除了绘制事件外不应该直接操作
                                                  //  PaintPtr Paint = nullptr; // 画笔,用于绘制,除了绘制事件外不应该直接操作
  std::set<HYObject *> Children;                  // 子对象
  std::unordered_map<intptr_t, intptr_t> UserData;// 用户数据

  // 判断给定坐标是否在当前对象范围内
  bool contains(int px, int py) const;
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
 * @param className 对象的类名，用于标识对象的类型。
 * @param name 对象的名称，用于标识对象。
 * @param id 对象的ID，用于标识对象。
 * @return HYObjectHandle 创建的对象的句柄。
 */
HYObjectHandle HYObjectCreate(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height,
                              const HYString &className, const HYString &name = "", int id = 0);

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
 * @brief 设置对象的类名称。
 *
 * 该函数用于为对象设置类名称。类名称可以用于标识对象的类型。
 *
 * @param object 待设置类名称的对象的句柄。
 * @param className 对象的新类名称。
 */
void HYObjectSetClassName(HYObjectHandle object, const HYString &className);

/**
 * @brief 设置对象的名称。
 *
 * 该函数用于为对象设置名称。名称可以用于标识对象。
 *
 * @param object 待设置名称的对象的句柄。
 * @param name 对象的新名称。
 */
void HYObjectSetName(HYObjectHandle object, const char *name);

/**
 * @brief 设置对象的ID。
 *
 * 该函数用于为对象设置ID。ID可以用于标识对象。
 *
 * @param object 待设置ID的对象的句柄。
 * @param id 对象的新ID。
 */
void HYObjectSetID(HYObjectHandle object, int id);

/**
 * @brief 同步向对象发送事件(call方式)。
 * 与HYObjectPushEvent的区别在于，HYObjectPushEventCall的底层是直接call消息链的。
 *
 * 该函数用于向指定的对象发送一个事件，对象可以根据事件类型执行相应的操作。
 * 例如，点击事件可能导致对象触发一个动作或改变其状态。
 *
 * @param window 窗口的指针，事件将在这个窗口内被处理。
 * @param object 接收事件的对象的句柄。
 * @param event 发送的事件类型,参考枚举值 HYObjectEvent。
 * @param param1 事件的第一个参数，具体含义取决于事件类型。
 * @param param2 事件的第二个参数，具体含义取决于事件类型。
 */
void HYObjectPushEventCall(HYWindow *window, HYObjectHandle object, HYObjectEvent event, int64_t param1, int64_t param2);

/**
 * @brief 同步向对象发送事件(event方式)。
 * 与HYObjectPushEventCall的区别在于，HYObjectPushEvent的底层是先投递消息到窗口,由窗口移交给消息链处理。
 *
 * 该函数用于向指定的对象发送一个事件，对象可以根据事件类型执行相应的操作。
 * 例如，点击事件可能导致对象触发一个动作或改变其状态。
 * @param window 窗口的指针，事件将在这个窗口内被处理。
 * @param object 接收事件的对象的句柄。
 * @param event 发送的事件类型,参考枚举值 HYObjectEvent。
 * @param param1 事件的第一个参数，具体含义取决于事件类型。
 * @param param2 事件的第二个参数，具体含义取决于事件类型。
 * */
void HYObjectPushEvent(HYWindow *window, HYObjectHandle object, HYObjectEvent event, int64_t param1, int64_t param2);

///**
// * @brief 向窗口内所有对象发送事件。
// *
// * @param window 窗口的指针，事件将在这个窗口内被处理。
// * @param object 接收事件的对象的句柄。
// * @param event 发送的事件类型。
// * @param param1 事件的第一个参数，具体含义取决于事件类型。
// * @param param2 事件的第二个参数，具体含义取决于事件类型。
// *
// * */
//void HYObjectSendEventLIst(HYWindow *window, int event, uint64_t param1, uint32_t param2);

/**
 * @brief 为对象设置用户数据。
 *
 * 该函数用于为指定的对象关联一组用户数据。这些数据可以是任何类型，
 * 通常用于存储与对象相关的额外信息。
 *
 * @param object 对象的句柄，将为该对象设置用户数据。
 * @param key 用户数据的键，用于标识特定的用户数据。
 * @param data 用户数据值。
 */
void HYObjectUserDataAdd(HYObjectHandle object, intptr_t key, intptr_t data);

/**
 * @brief 从对象获取用户数据。
 *
 * 该函数用于从指定的对象中获取与指定键关联的用户数据。
 *
 * @param object 对象的句柄，用于指定对象。
 * @param key 用户数据的键，用于标识特定的用户数据。
 * @param callback 回调函数，如果key存在则调用回调函数，回调为nullptr或者返回true删除数据，否则终止删除。
 */
void HYObjectUserDataRemove(HYObjectHandle object, intptr_t key,
                            const std::function<bool(HYObjectHandle object, intptr_t key,
                                                     intptr_t value)> &callback = nullptr);

/**
 * @brief 从鼠标位置获取对象句柄。
 *
 * 该函数用于从指定窗口的鼠标位置获取一个对象的句柄。
 * 如果鼠标位置在对象的范围内，则返回该对象的句柄；否则返回NULL。
 * 如果有多个对象在鼠标位置，则返回最上层非穿透的对象。
 *
 * @param window 窗口的指针，用于指定窗口。
 * @param x 鼠标的x坐标。
 * @param y 鼠标的y坐标。
 * @return HYObjectHandle 鼠标位置的对象的句柄。
 */
HYObjectHandle HYObjectGetFromMousePos(HYWindow *window, int x, int y);

/**
 * @brief 获取对象内某个坐标的绝对坐标。
 *
 * 该函数用于获取对象的绝对坐标，即对象中的点在窗口内的坐标。
 *
 * @param object 对象的句柄，用于指定对象。
 * @param x 对象内的x坐标。
 * @param y 对象内的y坐标。
 * */


/**
 * @brief 获取窗口坐标转换到对象内的相对坐标。
 *
 * 该函数用于将窗口坐标转换为对象内的相对坐标。
 *
 * @param object 对象的句柄，用于指定对象。
 * @param windowX 窗口的x坐标。
 * @param windowY 窗口的y坐标。
 * @return HYPoint 对象内的相对坐标。
 * */
HYPoint HYObjectGetRelativePoint(HYObjectHandle object, int windowX, int windowY);

/**
 * @brief 获取对象在窗口上嵌套裁剪后窗口坐标上的实际可视范围。
 *
 * 该函数用于计算并返回对象在窗口上，经过所有父级对象嵌套裁剪后，
 * 实际可视的矩形区域。
 *
 * @param object 对象的句柄，用于指定对象。
 * */
HYRect HYObjectGetNestedClippedVisibleArea(HYObjectHandle object);

/**
 * @brief 开始绘制对象。
 *
 * 该函数用于开始绘制指定对象。返回一个绘制对象的指针，用于绘制对象。
 *
 * @param object 对象的句柄，用于指定对象。
 * @param clear 是否清除背景,清除会将背景清除为透明。
 * @return PaintPtr 绘制对象的指针。
 * */
PaintPtr HYObjectBeginPaint(HYObjectHandle object, bool clear = true);

/**
 * @brief 结束绘制对象。
 *
 * 该函数用于结束绘制指定对象。释放绘制对象的资源。
 *
 * @param object 对象的句柄，用于指定对象。
 * @param repaint 绘制对象的指针。
 * */
void HYObjectEndPaint(HYObjectHandle object, SkPaint *repaint);

/**
 * @brief 获取对象是否可见。
 *
 * 该函数用于获取指定对象的可见性。
 *
 * @param object 对象的句柄，用于指定对象。
 * @return bool 是否可见。
 * */
bool HYObjectGetVisible(HYObjectHandle object);

/**
 * @brief 设置对象是否可见。
 *
 * 该函数用于设置指定对象的可见性。
 *
 * @param object 对象的句柄，用于指定对象。
 * @param visible 是否可见。
 * @param repaint 是否重绘。
 * */
void HYObjectSetVisible(HYObjectHandle object, bool visible,bool repaint = true);

}// namespace HYGUI

#endif//HYGUI_OBJECT_H
