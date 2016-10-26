#include "scene.h"
#include "sample.h"

Scene::Scene (Camera* camera) {
  this->camera = camera;
};

Film Scene::render (void) {
  Camera camera = *(this->camera);
  Sampler sampler (camera.width, camera.height);
  Film film (camera.width, camera.height);
  Sample sample;

  while (sampler.generateSample (sample)) {
    Ray ray = camera.generateRay (sample);
    Vec3 color = this->raytracer.trace (ray, 1);
    film.commit (sample, color);
  }

  return film;
};

void Scene::addPrimitive (Primitive* primitive) {
  this->raytracer.addPrimitive (primitive);
};

void Scene::addLight (Light* light) {
  this->raytracer.addLight (light);
};
