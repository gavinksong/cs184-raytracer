#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include "vec3.h"

class Transform {
  protected:
    Vec3 x, y, z, f;
  public:
    Transform (void);

    static Transform rotation (float x, float y, float z);
    static Transform scale (float x, float y, float z);
    static Transform translation (float x, float y, float z);
    
    Transform operator * (const Transform&) const;
    Vec3 operator * (const Vec3&) const;
    void operator *= (const Transform&);

    Transform inverse (void) const;
    Transform linear (void) const;

    friend std::ostream& operator << (std::ostream&, const Transform&);
};

#endif
