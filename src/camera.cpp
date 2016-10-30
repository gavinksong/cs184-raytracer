#include <cmath>
#include <limits>
#include "camera.h"

Camera::Camera (int width, int height) {
  float size = sqrt (width*width + height*height);
  this->width = width;
  this->height = height;
  this->eye = Vec3 (0, 0, 0);
  this->UL = Vec3 (-width,  height, -size);
  this->UR = Vec3 ( width,  height, -size);
  this->LR = Vec3 ( width, -height, -size);
  this->LL = Vec3 (-width, -height, -size);
};

Ray Camera::generateRay (const Sample& sample) const {
  Ray ray;
  float x = (float)sample.x / width;
  float y = (float)sample.y / height;
  ray.src = this->eye;
  ray.dir = (1-y) * ((1-x) * this->UL + x * this->UR)
          + y * ((1-x) * this->LL + x * this->LR) - ray.src;
  ray.tmax = std::numeric_limits<float>::infinity ();
  return ray;
};

void Camera::transform (const Transform& t) {
  this->eye = t * this->eye;
  this->UL = t * this->UL;
  this->UR = t * this->UR;
  this->LR = t * this->LR;
  this->LL = t * this->LL;
};
