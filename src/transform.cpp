#include <math.h>
#include "transform.h"

Transform::Transform (void) {
  this->x.assign (1, 0, 0);
  this->y.assign (0, 1, 0);
  this->z.assign (0, 0, 1);
  this->f.assign (0, 0, 0);
};

Transform Transform::scale (float x, float y, float z) {
  Transform temp;
  temp.x.x = x;
  temp.y.y = y;
  temp.z.z = z;
  return temp;
};

Transform Transform::translation (float x, float y, float z) {
  Transform temp;
  temp.f.assign (x, y, z);
  return temp;
};

Transform Transform::operator * (const Transform& t) const {
  Transform linear = this->linear ();
  Transform temp;
  temp.x = linear * t.x;
  temp.y = linear * t.y;
  temp.z = linear * t.z;
  temp.f = *this * t.f;
  return temp;
};

Vec3 Transform::operator * (const Vec3& v) const {
  Vec3 temp = this->f;
  temp += this->x * v.x;
  temp += this->y * v.y;
  temp += this->z * v.z;
  return temp;
};

void Transform::operator *= (const Transform& t) {
  *this = *this * t;
};

Transform Transform::inverse (void) const {
  Vec3 x = this->x;
  Vec3 y = this->y;
  Vec3 z = this->z;

  float det = x.x * (y.y * z.z - y.z * z.y)
            - y.x * (z.y * x.z - z.z * x.y)
            + z.x * (x.y * y.z - x.z * y.y);

  Transform inv;
  inv.x.assign ((y.y * z.z - y.z * z.y) / det,
                (y.z * z.x - y.x * z.z) / det,
                (y.x * z.y - y.y * z.x) / det);
  inv.y.assign ((z.y * x.z - z.z * x.y) / det,
                (z.z * x.x - z.x * x.z) / det,
                (z.x * x.y - z.y * x.x) / det);
  inv.z.assign ((x.y * y.z - x.z * y.y) / det,
                (x.z * y.x - x.x * y.z) / det,
                (x.x * y.y - x.y * y.x) / det);
  inv.f = -(inv * this->f);
  return inv;
};

Transform Transform::linear (void) const {
  Transform temp = *this;
  temp.f.assign (0, 0, 0);
  return temp;
}

std::ostream& operator << (std::ostream& out, const Transform& t) {
  out << "(" << t.x << "\n " << t.y << "\n " << t.z << "\n " << t.f << ")";
  return out;
};
