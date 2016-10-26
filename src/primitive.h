#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "material.h"
#include "localgeo.h"
#include "ray.h"
#include "transform.h"
#include "vec3.h"

class Primitive {
  public:
    Material material;
    bool intersectP (const Ray&) const;
    virtual bool intersect (const Ray&, float&, LocalGeo&) const =0;
    virtual void transform (const Transform&) =0;
};

#endif
