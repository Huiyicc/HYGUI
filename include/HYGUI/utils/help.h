//
// Created by 19254 on 24-5-13.
//

#ifndef HYGUI_HELP_H
#define HYGUI_HELP_H

#include <HYGUI/core/define.h>

namespace HYGUI {

/**
 * 获取工作区域的矩形范围
 *
 * 本函数用于获取系统的工作区域的矩形范围。工作区域是指屏幕中除去任务栏和侧边栏等系统界面后的可用区域。
 *
 * @param rc 指向RECT结构体的指针，用于接收工作区域的矩形范围。
 */
void GetWorkingAreaRECT(HRECT *rc);

}


#endif //HYGUI_HELP_H
