//
// Created by 19254 on 24-5-13.
//

#ifndef HYGUI_WINDOW_H
#define HYGUI_WINDOW_H

#include <HYGUI/core/define.h>
#include <HYGUI/core/HString.h>
#include <string>

namespace HYGUI {

/**
 * @brief 窗口句柄
 */
typedef void *WINDOWHAND;

/**
 * 创建一个新窗口。
 *
 * @param parent 父窗口的句柄，如果没有父窗口则传入nullptr。
 * @param left 窗口左上角相对于屏幕的X坐标，如果使用默认值则自动计算。
 * @param top 窗口左上角相对于屏幕的Y坐标，如果使用默认值则自动计算。
 * @param width 窗口的宽度，默认为800。
 * @param height 窗口的高度，默认为600。
 * @param title 窗口的标题，默认为空字符串。
 * @param isResizable 窗口是否可调整大小，默认为true。
 * @param style 窗口的样式，采用位或操作组合多个WINDOWSTYLE中的样式，默认包含系统菜单、最大化框、最小化按钮、剪裁子窗口和弹出窗口样式。
 * @param taskbar 是否在任务栏中显示该窗口的按钮，默认为true。
 * @return 返回新创建窗口的句柄。
 */
WINDOWHAND
HCreateWindow(WINDOWHAND parent = nullptr,
              float left = WINDOWPOS_USEDEFAULE, float top = WINDOWPOS_USEDEFAULE,
              float width = 800, float height = 600,
              const HString& title = "",
              bool isResizable = true,
              uint32_t style = WINDOWSTYLE::WINDOWSTYLE_SYSMENU |
                                                           WINDOWSTYLE::WINDOWSTYLE_MAXIMIZEBOX |
                                                           WINDOWSTYLE::WINDOWSTYLE_MINIMIZE |
                                                           WINDOWSTYLE::WINDOWSTYLE_CLIPCHILDREN |
                                                           WINDOWSTYLE::WINDOWSTYLE_POPUP,
                                                           bool taskbar = true
);

/**
 * 注册一个窗口类。
 *
 * @param className 窗口类的名称，类型为std::string_view，不可为空。
 * @return 若注册成功返回true，否则返回false。
 */
bool HRegisterWindowClass(HString className);

/**
 * 进入消息循环处理。
 *
 * @param hWnd 窗口的句柄，类型为WINDOWHAND。
 * @return 处理消息循环期间接收的消息数量，类型为uint32_t。
 */
uint32_t HWindowMessageLoop(WINDOWHAND hWnd);

/**
 * @brief 这个函数用于处理与特定窗口相关的消息循环。
 *
 * @param parent 父窗口的句柄。这个参数指定了对话框的父窗口。
 * @param hWnd 对话框的窗口句柄。这个参数标识了需要进行消息处理的窗口。
 * @return uint32_t 函数执行的结果状态码。返回值通常用于指示操作的成功或失败。
 */
uint32_t HWindowMessageLoopDialog(WINDOWHAND parent,WINDOWHAND hWnd);


}

#endif //HYGUI_WINDOW_H
