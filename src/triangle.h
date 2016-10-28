#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"
#include "transform.h"
#include "vec3.h"

class Triangle: public Primitive {
  protected:
    Vec3 a, b, c;
  public:
    Triangle () {};
    Triangle (Vec3& a, Vec3& b, Vec3& c) : a(a), b(b), c(c) {};
    bool intersect (const Ray&, float&, LocalGeo&) const;
    void transform (const Transform&);
};

#endif
