//
// Created by 19254 on 24-6-24.
//

#ifndef HYGUI_CURSOR_H
#define HYGUI_CURSOR_H

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

};

#endif //HYGUI_CURSOR_H
