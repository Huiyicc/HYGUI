# HYInit

> namespace HYGUI

## **功能**
初始化HYGUI库，设置全局标志、默认光标和类名。

## **函数原型**
```C++
bool HYInit(VOIDPTR ModuleHandle,
            HYGlobalFlag DefaultGlobalFlags,
            CursorPtr DefaultCursor=nullptr);
```

## **参数**
- `ModuleHandle` (VOIDPTR)：模块句柄。
- `DefaultGlobalFlags` (HYGlobalFlag)：默认的全局标志。
- `DefaultCursor` (CursorPtr, 可选)：默认光标，默认值为nullptr。
- `DefaultClassName` (HYString, 可选)：默认窗口类名，。

## **返回值**
- `bool`：初始化成功返回true，失败返回false。