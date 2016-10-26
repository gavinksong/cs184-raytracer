#include <cmath>
#include "material.h"

inline float sqr (float x) { return x*x; };

Vec3 Material::brdf (const Vec3& view, const Vec3& light, const Vec3& normal) const {
  Vec3 v = normalize (view);
  Vec3 l = normalize (light);
  Vec3 n = normalize (normal);

  Vec3 y (0, 1, 0);
  Vec3 r = n.reflect (l);
  Vec3 h = normalize (l + v);
  Vec3 pv = normalize (y - n * (n * y));
  Vec3 pu = cross (pv, n);

  float p = this->spu * sqr (h * pu) + this->spv * sqr (h * pv);
  return this->ka
       + this->kd * fmaxf (n * l, 0)
       + this->ks * pow (fmaxf (r * v, 0), p);
};
