#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

class Material {
  public:
    static Material matte (void);

    Vec3 ka, ks, kd;
    float kr, spu, spv;
    Vec3 brdf (const Vec3& v, const Vec3& l, const Vec3& n) const;
};

#endif
