#include <limits>
#include "camera.h"

Camera::Camera (int width, int height) {
  this->width = width;
  this->height = height;
  this->eye.assign (0, 0, 0);
  this->UL.assign (-100./height,  100./width, -1);
  this->UR.assign ( 100./height,  100./width, -1);
  this->LR.assign ( 100./height, -100./width, -1);
  this->LL.assign (-100./height, -100./width, -1);
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
