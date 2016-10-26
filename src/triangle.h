#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"
#include "transform.h"
#include "vec3.h"

class Triangle: public Primitive {
  protected:
    Vec3* a, b, c;
  public:
    Triangle () {};
    Triangle (const Vec3& a, const Vec3& b, const Vec3& c) : a(a), b(b), c(c) {};
    void transform (const Transform&);
    bool intersect (const Ray& ray, float& thit, LocalGeo& out) const;
    void debug (void) const;
};

#endif
