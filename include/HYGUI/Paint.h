//
// Created by 19254 on 2024/6/17.
//

#ifndef HYGUI_PAINT_H
#define HYGUI_PAINT_H

#include <HYGUI/Define.h>
#include <HYGUI/Color.h>

namespace HYGUI {

/**
 * @brief 设置画笔颜色
 * @param paint 画笔指针
 * @param color 颜色
 * */
void HYPaintSetColor(PaintPtr paint, HYARGB color);

/**
 * @brief 设置画笔颜色
 * @param paint 画笔指针
 * @param a 透明度
 * @param r 红色
 * @param g 绿色
 * @param b 蓝色
 * */
void HYPaintSetARGB(PaintPtr paint, uint8_t a, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief 绘制矩形
 * @param canvas 画布指针
 * @param paint 画笔指针
 * @param rect 矩形
 * */
void HYPaintDrawRect(CanvasPtr canvas,PaintPtr paint,const HYRect* rect);

/**
 * @brief 绘制圆角矩形
 * @param canvas 画布指针
 * @param paint 画笔指针
 * @param rect 矩形
 * @param rx x轴圆角半径
 * @param ry y轴圆角半径
 * */
void HYPaintDrawRoundRect(CanvasPtr canvas,PaintPtr paint,const HYRect* rect,float rx,float ry);

/**
 * @brief 设置画笔着色器
 * @param paint 画笔指针
 * @param shader 着色器指针
 * */
void HYPaintSetShader(PaintPtr paint,ShaderPtr shader);

}

#endif //HYGUI_PAINT_H
