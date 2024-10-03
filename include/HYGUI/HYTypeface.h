//
// Created by 19254 on 24-10-1.
//

#ifndef HYGUI_HYTYPEFACE_H
#define HYGUI_HYTYPEFACE_H

class SkTypeface;

namespace HYGUI {

class HYTypeface: public HYClassBase {
public:
  ~HYTypeface() override;

  explicit HYTypeface();
  explicit HYTypeface(SkTypeface* ptr);

  SkTypeface* operator->();
  bool operator==(const nullptr_t&p);
  bool operator!();


private:
  std::shared_ptr<SkTypeface> m_ptr;
};


}

#endif//HYGUI_HYTYPEFACE_H
