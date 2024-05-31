//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_IMAGE_H
#define HYGUI_IMAGE_H

#include "HYGUI/Define.h"

namespace HYGUI {

/**
 * @brief 从文件创建图像指针
 * @param path
 * @return
 * */
ImagePtr HYImageLoadFromFile(const HYString& path);

/**
 * @brief 从文件创建光标指针
 * @param path
 * @return
 * */
CursorPtr HYCursorLoadFromFile(const HYString& path);

/**
 * @brief 从图像指针创建光标指针
 * @param image
 * @return
 * */
CursorPtr HYCursorLoadFromImage(ImagePtr image);

/**
 * @brief 从默认光标创建光标指针
 * @return
 * */
CursorPtr HYCursorLoadFromDefault();

}

#endif //HYGUI_IMAGE_H
