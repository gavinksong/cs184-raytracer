#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include "light.h"
#include "primitive.h"
#include "ray.h"
#include "vec3.h"

class RayTracer {
  protected:
    std::vector<Primitive*> primitives;
    std::vector<Light*> lights;
    bool intersect (Ray&, Primitive*&, LocalGeo&);
    bool intersectP (Ray&);
  public:
    Vec3 trace (Ray ray, int depth);
    void addPrimitive (Primitive*);
    void addLight (Light*);
};

#endif
