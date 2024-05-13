//
// Created by 19254 on 24-5-13.
//

#ifndef HYGUI_DEFINE_H
#define HYGUI_DEFINE_H

#include <cstdint>

namespace HYGUI {

constexpr const wchar_t* WINDOWCLASSNAME = L"HYGUI_WINDOW"; /**< 窗口类名 */

/**
 * @struct HPoint
 *
 * 代表一个二维坐标点的结构体。
 *
 * @field float X 坐标点的x轴坐标。
 * @field float Y 坐标点的y轴坐标。
 */
struct HPoint {
  float X; // X轴坐标
  float Y; // Y轴坐标
};

/**
 * @struct HRECT
 *
 * 该结构体定义了一个矩形的区域，使用浮点数来表示矩形的左上角和右下角的坐标。
 */
struct HRECT {
  float Left;    /**< 矩形左边界横坐标 */
  float Top;     /**< 矩形上边界纵坐标 */
  float Right;   /**< 矩形右边界横坐标 */
  float Bottom;  /**< 矩形下边界纵坐标 */
};


enum WINDOWPOS {
  WINDOWPOS_USEDEFAULE = 0x80000 /**< 使用默认位置 */
};

/**
 * @enum WINDOWSTYLE
 *
 * 该枚举类型定义了窗口的风格。
 * (有些窗口不一定有效)
 */
enum WINDOWSTYLE : uint32_t {
  WINDOWSTYLE_OVERLAPPED = 0x00000000L, /**< 重叠窗口 */
  WINDOWSTYLE_POPUP = 0x80000000L, /**< 弹出窗口 */
  WINDOWSTYLE_CHILD = 0x40000000L, /**< 子窗口 */
  WINDOWSTYLE_MINIMIZE = 0x20000000L, /**< 最小化窗口 */
  WINDOWSTYLE_VISIBLE = 0x10000000L, /**< 可见窗口 */
  WINDOWSTYLE_DISABLED = 0x08000000L, /**< 禁用窗口 */
  WINDOWSTYLE_CLIPSIBLINGS = 0x04000000L, /**< 剪切兄弟窗口 */
  WINDOWSTYLE_CLIPCHILDREN = 0x02000000L, /**< 剪切子窗口 */
  WINDOWSTYLE_MAXIMIZE = 0x01000000L, /**< 最大化窗口 */
  WINDOWSTYLE_CAPTION = 0x00C00000L, /**< 标题栏 */
  WINDOWSTYLE_BORDER = 0x00800000L, /**< 边框 */
  WINDOWSTYLE_DLGFRAME = 0x00400000L, /**< 对话框框架 */
  WINDOWSTYLE_VSCROLL = 0x00200000L, /**< 垂直滚动条 */
  WINDOWSTYLE_HSCROLL = 0x00100000L, /**< 水平滚动条 */
  WINDOWSTYLE_SYSMENU = 0x00080000L, /**< 系统菜单 */
  WINDOWSTYLE_THICKFRAME = 0x00040000L, /**< 窗口边框 */
  WINDOWSTYLE_GROUP = 0x00020000L, /**< 组 */
  WINDOWSTYLE_TABSTOP = 0x00010000L, /**< Tab键停止 */
  WINDOWSTYLE_MINIMIZEBOX = 0x00020000L, /**< 最小化按钮 */
  WINDOWSTYLE_MAXIMIZEBOX = 0x00010000L, /**< 最大化按钮 */
  WINDOWSTYLE_WINDOWSTYLE_TILED = WINDOWSTYLE_OVERLAPPED, /**< 平铺窗口 */
  WINDOWSTYLE_ICONIC = WINDOWSTYLE_MINIMIZE, /**< 图标化窗口 */
  WINDOWSTYLE_SIZEBOX = WINDOWSTYLE_THICKFRAME, /**< 大小框 */
};

enum WINDOWSTYLEEX : uint32_t {
  WINDOWSTYLEEX_APPWINDOW = 0x00040000L, /**< 应用程序窗口 */
  WINDOWSTYLEEX_TOOLWINDOW = 0x00000080L, /**< 工具窗口 */
};

}

#endif //HYGUI_DEFINE_H
