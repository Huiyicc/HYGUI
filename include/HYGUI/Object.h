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
};



HYObjectHandle HYObjectCreate(HYWindow *window, HYObjectHandle parent, int x, int y, int width, int height);

void HYObjectDestroy(HYObjectHandle object);

int HYObjectSendEvent(HYObjectHandle object, int event, int param1, int param2);

void HYObjectAddEventCallback(HYObjectHandle object, const HYObjectEventCallback& callback);

}

#endif //HYGUI_OBJECT_H
