#include <cmath>
#include "sphere.h"

Sphere::Sphere (float x, float y, float z, float r) {
  this->transmat = Transform::translation (x, y, z);
  this->transmat *= Transform::scale (r, r, r);
};

void Sphere::transform (const Transform& t) {
  this->transmat = t * this->transmat;
};

bool Sphere::intersect (const Ray& ray, float& thit, LocalGeo& out) const {
  Transform inv = this->transmat.inverse ();
  Vec3 src = inv * ray.src;
  Vec3 dir = inv.linear () * ray.dir;

  float a = dir * dir;
  float b = 2 * src * dir;
  float c = src * src - 1;
  float det = b*b - 4*a*c;

  if (det < 0) return false;
  float t = -(b + sqrt(det)) / (2*a);
  if (t <= 0 || t > ray.tmax) return false;

  Vec3 v = src + t * dir;
  out.pos = this->transmat * v;
  out.normal = normalize (inv.linearT () * v);
  thit = t;
  return true;
};
