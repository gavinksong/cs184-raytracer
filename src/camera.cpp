#include <cmath>
#include <limits>
#include "camera.h"

Camera::Camera (int width, int height) {
  this->width = width;
  this->height = height;
  this->eye.assign (0, 0, 0);
  this->autoResize ();
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

void Camera::autoResize (void) {
  float width = this->width;
  float height = this->height;
  float size = sqrt (width*width + height*height);
  this->UL.assign (-width,  height, -size);
  this->UR.assign ( width,  height, -size);
  this->LR.assign ( width, -height, -size);
  this->LL.assign (-width, -height, -size);
};
