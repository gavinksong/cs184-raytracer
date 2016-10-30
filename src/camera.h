#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "sample.h"
#include "transform.h"
#include "vec3.h"

class Camera {
  public:
    Vec3 eye, UL, UR, LR, LL;
    int width, height;

    Camera (int width, int height);
    Ray generateRay (const Sample&) const;
    void transform (const Transform&);
};

#endif
