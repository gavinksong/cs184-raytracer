#include <iostream>
#include "triangle.h"

void Triangle::transform (const Transform& t) {
  this->a = t * this->a;
  this->b = t * this->b;
  this->c = t * this->c;
};

bool Triangle::intersect (const Ray& ray, float& thit, LocalGeo& out) const {
  Vec3 ab = this->b - this->a;
  Vec3 ac = this->c - this->a;
  Vec3 diff = this->a - ray.pos;

  Vec3 normal = normalize (cross (ab, ac));
  float t = (diff * normal) / (ray.dir * normal);

  if (t <= 0 || t > ray.tmax)
    return false;

  Vec3 ax = ray.dir * t - diff;
  float beta = (ax * ab) / (ab * ab);
  float gamma = (ax * ac) / (ac * ac);
  if (beta < 0 || gamma < 0 || beta + gamma > 1)
    return false;

  out.pos = this->a + ax;
  out.normal = normal;
  thit = t;
  return true;
};
