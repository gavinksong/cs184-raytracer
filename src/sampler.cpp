#include "sampler.h"

Sampler::Sampler (int width, int height) {
  this->width = width;
  this->height = height;
  this->posX = .5;
  this->posY = .5;
};

bool Sampler::generateSample (Sample& sample) {
  if (this->posY > this->height) return false;
  sample.x = this->posX;
  sample.y = this->posY;
  this->posX += 1;
  if (this->posX > this->width) {
    this->posX = .5;
    this->posY += 1;
  }
  return true;
};
