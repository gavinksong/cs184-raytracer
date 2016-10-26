#include <string.h>
#include "film.h"

Film::Film (int width, int height) : width(width), height(height) {
  this->pixels = new Vec3*[width];
  this->numCommits = new float*[width];
  for (int i = 0; i < width; i++) {
    this->pixels[i] = new Vec3[height];
    this->numCommits[i] = new float[height];
    memset (this->numCommits[i], 0, sizeof (float) * height);
  }
};

Film::~Film (void) {
  for (int i = 0; i < this->width; i++) {
    delete [] this->pixels[i];
    delete [] this->numCommits[i];
  }
  delete [] this->pixels;
  delete [] this->numCommits;
};

void Film::commit (const Sample& sample, const Vec3& color) {
  int x = (int)sample.x;
  int y = (int)sample.y;

  Vec3* pixel = &(this->pixels[x][y]);
  float* count = &(this->numCommits[x][y]);

  if (*count++ == 0)
    *pixel = color;
  else
    *pixel = (*pixel * (*count-1) + color) / *count;
};

Vec3 Film::getColorAt (int x, int y) const {
  return this->pixels[x][y];
};
