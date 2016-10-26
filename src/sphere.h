#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include "transform.h"

class Sphere: public Primitive {
  protected:
    Transform transmat;
  public:
    Sphere () {};
    Sphere (float x, float y, float z, float r);
    void transform (const Transform&);
    bool intersect (const Ray& ray, float& thit, LocalGeo& out) const;
};

#endif
