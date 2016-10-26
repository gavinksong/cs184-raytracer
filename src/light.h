#ifndef LIGHT_H
#define LIGHT_H

#include "localgeo.h"
#include "ray.h"
#include "vec3.h"

class Light {
  public:
    Vec3 xyz;
    Vec3 rgb;

    virtual Ray generateLightRay (const LocalGeo&) const =0;
};

class PointLight: public Light {
  public:
    Ray generateLightRay (const LocalGeo&) const;
};

class DirectionalLight: public Light {
  public:
    Ray generateLightRay (const LocalGeo&) const;
};

#endif
