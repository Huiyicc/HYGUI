//
// Created by 回忆 on 24-10-6.
//

#ifndef HYCURSOR_H
#define HYCURSOR_H

#include "HYTypeDef.h"
#include <memory>

struct SDL_Cursor;

namespace HYGUI {

enum HY_SYSTEM_CURSOR {
  HY_SYSTEM_CURSOR_ARROW,     /**< Arrow */
  HY_SYSTEM_CURSOR_IBEAM,     /**< I-beam */
  HY_SYSTEM_CURSOR_WAIT,      /**< Wait */
  HY_SYSTEM_CURSOR_CROSSHAIR, /**< Crosshair */
  HY_SYSTEM_CURSOR_WAITARROW, /**< Small wait cursor (or Wait if not available) */
  HY_SYSTEM_CURSOR_SIZENWSE,  /**< Double arrow pointing northwest and southeast */
  HY_SYSTEM_CURSOR_SIZENESW,  /**< Double arrow pointing northeast and southwest */
  HY_SYSTEM_CURSOR_SIZEWE,    /**< Double arrow pointing west and east */
  HY_SYSTEM_CURSOR_SIZENS,    /**< Double arrow pointing north and south */
  HY_SYSTEM_CURSOR_SIZEALL,   /**< Four pointed arrow pointing north, south, east, and west */
  HY_SYSTEM_CURSOR_NO,        /**< Slashed circle or crossbones */
  HY_SYSTEM_CURSOR_HAND,      /**< Hand */
};

class HYCursor : public HYClassBase {
public:
  HYCursor();
  explicit HYCursor(SDL_Cursor*);

  ~HYCursor() override;

  HYGUICLASS_HANDER_DEFINE(HYCursor,SDL_Cursor);

  HYCursor& operator=(const nullptr_t &p);

  static HYCursor MakeFromSystemCursor(HY_SYSTEM_CURSOR);
};

};

#endif //HYCURSOR_H
