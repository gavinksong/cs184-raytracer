#ifndef FILM_H
#define FILM_H

#include "sample.h"
#include "vec3.h"

class Film {
  private:
    int width, height;
    Vec3** pixels;
    float** numCommits;
  public:
    Film (int width, int height);
    ~Film (void);
    void commit (const Sample&, const Vec3& color);
    Vec3 getColorAt (int x, int y) const;
};

#endif
