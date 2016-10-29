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
  Vec3 diff = this->a - ray.src;

  Vec3 normal = normalize (cross (ab, ac));
  float t = (diff * normal) / (ray.dir * normal);

  if (t <= 0 || t > ray.tmax)
    return false;

  Vec3 x = ray.src + ray.dir * t;
  Vec3 bc = this->c - this->b;
  if (normal * cross (ab, x - this->a) < 0 ||
      normal * cross (bc, x - this->b) < 0 ||
      normal * cross (-ac, x - this->c) < 0)
    return false;

  out.pos = x;
  out.normal = normal;
  thit = t;
  return true;
};
