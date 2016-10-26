#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "film.h"
#include "raytracer.h"
#include "sampler.h"
#include "vec3.h"

class Scene {
  protected:
    Camera* camera;
    RayTracer raytracer;
  public:
    Scene (Camera* camera);
    Film render (void);
    void addPrimitive (Primitive*);
    void addLight (Light*);
};

#endif
