#ifndef SAMPLER_H
#define SAMPLER_H

#include "sample.h"

class Sampler {
  protected:
    int width, height;
    float posX, posY;
  public:
    Sampler (int width, int height);
    bool generateSample (Sample& sample);
};

#endif
