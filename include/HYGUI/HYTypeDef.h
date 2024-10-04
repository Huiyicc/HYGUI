//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_TYPEDEF_H
#define HYGUI_TYPEDEF_H

//#ifdef _HYGUI_MODULE_
//
//#include "include/core/SkBitmap.h"
//#include "include/core/SkCanvas.h"
//#include "include/core/SkData.h"
//#include "include/core/SkFontMgr.h"
//#include "include/core/SkImage.h"
//#include "include/core/SkPaint.h"
//#include "include/core/SkSurface.h"
//#include "include/core/SkTextBlob.h"
//#include "include/core/SkRefCnt.h"
//class SkShader;
//
//#else
//
//class SkImage;
//class SkSurface;
//class SkCanvas;
//class SkPaint;
//class SkTypeface;
//class SkFont;
//class SkFontMgr;
//class SkTextBlobBuilder;
//class SkShader;
//
//
//#endif

class SkImage;

template<class T>
class sk_sp;

struct SDL_Window;
struct SDL_GLContextState;
typedef struct SDL_GLContextState *SDL_GLContext;
typedef void *VOIDPTR;

namespace HYGUI {

class HYClassBase {
public:
  virtual ~HYClassBase() = default;
};

/**
 * @brief 图像
 * */
class HYImage;

/**
 * @brief 纹理
 * */
class HYSurface;

/**
 * @brief 画布
 * */
class HYCanvas;
/**
 * @brief 画笔
 * */
class HYPaint;
/**
 * @brief 字形
 * */
class HYTypeface;
/**
 * @brief 字体
 * */
class HYFont;
/**
 * @brief 字体样式
 * */
class HYFontStyle;
/**
 * @brief 字体管理器
 * */
class HYFontMgr;
///**
// * @brief 文本块构建器指针
// * */
//typedef SkTextBlobBuilder *TextBlobBuilderPtr;
/**
 * @brief 着色器
 * */
class HYShader;

}// namespace HYGUI

#define HYGUICLASS_HANDER_DEFINE(CLASSTYPE, PKGTYPE) \
private:                                             \
  std::shared_ptr<PKGTYPE> m_ptr;                 \
                                                     \
public:                                              \
  PKGTYPE *get() const;                              \
  PKGTYPE *operator->() const;                       \
  bool operator==(const nullptr_t &p) const;\
 bool operator!() const;



#endif//HYGUI_TYPEDEF_H
