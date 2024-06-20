//
// Created by 19254 on 24-6-4.
//

#ifndef HYGUI_DRAW_H
#define HYGUI_DRAW_H



namespace HYGUI {

#ifdef _HYGUI_MODULE_



#else

#define SkImage void
#define SkSurface void
#define SkCanvas void
#define SkPaint void


#endif

typedef SkImage *ImagePtr;
typedef SkSurface *SurfacePtr;
typedef SkCanvas *CanvasPtr;
typedef SkPaint *PaintPtr;

}

#endif //HYGUI_DRAW_H
