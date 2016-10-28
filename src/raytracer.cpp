#include "material.h"
#include "localgeo.h"
#include "raytracer.h"

bool RayTracer::intersect (Ray& ray, Primitive*& p, LocalGeo& local) {
  bool retval = false;
  for (std::vector<Primitive *>::iterator it = this->primitives.begin ();
       it != this->primitives.end ();
       it++) {
    if ((*it)->intersect (ray, ray.tmax, local)) {
      p = *it;
      retval = true;
    }
  }
  return retval;
}

bool RayTracer::intersectP (Ray& ray) {
  Primitive* p;
  LocalGeo local;
  return this->intersect (ray, p, local);
};

Vec3 RayTracer::trace (Ray ray, int depth) {
  Primitive* primitive;
  LocalGeo local;
  Vec3 color (0, 0, 0);

  if (depth <= 0) {
    return color;
  }

  if (this->intersect (ray, primitive, local)) {
    Material* mat = &primitive->material;

    for (std::vector<Light*>::iterator it = this->lights.begin ();
         it != this->lights.end ();
         it++) {
      Light* light = *it;
      Ray lray = light->generateLightRay (local);

      // Add bias to avoid self-shadowing
      Ray sray = lray;
      sray.src += local.normal * .00001;
      
      // Shade if light is not blocked
      if (!this->intersectP (sray)) {
        Vec3 shading = mat->brdf (-ray.dir, lray.dir, local.normal);
        color += hadamard (light->rgb, shading);
      }
    }
    
    // Handle mirror reflection
    if (mat->kr > 0) {
      Ray reflectRay;
      reflectRay.src = local.pos + local.normal * .00001;
      reflectRay.dir = local.normal.reflect (-ray.dir);
      reflectRay.tmax = std::numeric_limits<float>::infinity ();

      // Make a recursive call to trace the reflected ray
      color += mat->kr * this->trace (reflectRay, depth-1);
    }
  }

  return color;
};

void RayTracer::addPrimitive (Primitive* p) {
  this->primitives.push_back (p);
};

void RayTracer::addLight (Light* l) {
  this->lights.push_back (l);
};
