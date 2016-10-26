#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Ray {
  Vec3 src;
  Vec3 dir;
  float tmax;
};

#endif
