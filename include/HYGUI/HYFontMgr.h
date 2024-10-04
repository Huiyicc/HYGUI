//
// Created by 19254 on 24-9-30.
//

#ifndef HYGUI_HYFONTMGR_H
#define HYGUI_HYFONTMGR_H

#include <HYGUI/HYDefine.h>
#include <memory>

class SkFontMgr;

namespace HYGUI {

class HYFontMgr: public HYClassBase {
public:
  ~HYFontMgr() override;

  explicit HYFontMgr();
  explicit HYFontMgr(SkFontMgr* ptr);

  SkFontMgr* operator->() const;
  bool operator==(const nullptr_t&p) const;
  bool operator!() const;

private:
  std::shared_ptr<SkFontMgr> m_ptr;
};

}

#endif//HYGUI_HYFONTMGR_H
