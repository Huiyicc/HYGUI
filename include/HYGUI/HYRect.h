//
// Created by 回忆 on 24-10-4.
//

#ifndef HYRECT_H
#define HYRECT_H

namespace  HYGUI {

struct HYRect {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

struct HYRectf {
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

struct HYRRect {
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float xRad = 0.0f;
  float yRad = 0.0f;

};


};

#endif //HYRECT_H
