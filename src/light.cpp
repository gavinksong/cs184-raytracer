#include <limits>
#include "light.h"

Ray PointLight::generateLightRay (const LocalGeo& local) const {
  Ray ray;
  ray.src = local.pos;
  ray.dir = this->xyz - ray.src;
  ray.tmax = 1;
  return ray;
};

Ray DirectionalLight::generateLightRay (const LocalGeo& local) const {
  Ray ray;
  ray.src = local.pos;
  ray.dir = -this->xyz;
  ray.tmax = std::numeric_limits<float>::infinity ();
  return ray;
};
