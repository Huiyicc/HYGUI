//
// Created by 19254 on 24-7-27.
//

#ifndef HYGUI_UTILS_H
#define HYGUI_UTILS_H

namespace HYGUI {

/**
 * @brief 合并两个32位无符号整数
 * */
#define HYCombineUint32(high, low) ((static_cast<int64_t>(high) << 32) | (low))

/**
 * @brief 获取高32位
 * */
#define HYGetHighUint32(x) ((x) >> 32)

/**
 * @brief 获取低32位
 * */
#define HYGetLowUint32(x) ((x) & 0xFFFFFFFF)

}


#endif//HYGUI_UTILS_H
