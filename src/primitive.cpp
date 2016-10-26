#include "primitive.h"

bool Primitive::intersectP (const Ray& ray) const {
  float thit;
  LocalGeo local;
  return this->intersect (ray, thit, local);
};
