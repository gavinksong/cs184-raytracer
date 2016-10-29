#include <fstream>
#include <string>
#include <vector>
#include "material.h"
#include "sample.h"
#include "scene.h"
#include "sphere.h"
#include "transform.h"
#include "triangle.h"

using namespace std;

vector<string> split (const string& s, const string& delims);

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
    Vec3 color = this->raytracer.trace (ray, recursiveDepth);
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

void Scene::readFile (const char* filename) {
  ifstream file (filename);
  string delims (" \t");
  string line;
  vector<Vec3> points;
  vector<Vec3> colors;
  vector<Material> materials;
  vector<Primitive*> primitives;
  if (file.is_open ()) {
    while (getline (file, line)) {
      vector<string> tokens = split (line, delims);
      if (!tokens.empty ()) {
        if (tokens[0] == "v") {
          points.push_back (Vec3 (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3])));
        } else if (tokens[0] == "f") {
          // TODO: memory leak :))))
          Triangle* t = new Triangle (
            points[stoi (tokens[1]) - 1],
            points[stoi (tokens[2]) - 1],
            points[stoi (tokens[3]) - 1]);
          if (tokens.size () > 4)
            t->material = materials[stoi (tokens[4]) - 1];
          else
            t->material = Material::matte ();
          primitives.push_back (t);
        } else if (tokens[0] == "s") {
          Sphere* s = new Sphere (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3]),
            stof (tokens[4]));
          if (tokens.size () > 5)
            s->material = materials[stoi (tokens[5]) - 1];
          else
            s->material = Material::matte ();
          primitives.push_back (s);
        } else if (tokens[0] == "c") {
          colors.push_back (Vec3 (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3])));
        } else if (tokens[0] == "m") {
          Material mat;
          mat.ka = colors[stoi (tokens[1]) - 1];
          mat.kd = colors[stoi (tokens[2]) - 1];
          mat.ks = colors[stoi (tokens[3]) - 1];
          mat.kr = stof (tokens[4]);
          mat.spu = stof (tokens[5]);
          mat.spv = stof (tokens[6]);
          materials.push_back (mat);
        } else if (tokens[0] == "dl") {
          DirectionalLight* dl = new DirectionalLight ();
          dl->xyz = Vec3 (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3]));
          dl->rgb = colors[stoi (tokens[4]) - 1];
          this->raytracer.addLight (dl);
        } else if (tokens[0] == "pl") {
          PointLight* pl = new PointLight ();
          pl->xyz = Vec3 (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3]));
          pl->rgb = colors[stoi (tokens[4]) - 1];
          this->raytracer.addLight (pl);
        } else if (tokens[0] == "tr") {
          Primitive* p = primitives[stoi (tokens[4]) - 1];
          p->transform (Transform::rotation (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3])));
        } else if (tokens[0] == "ts") {
          Primitive* p = primitives[stoi (tokens[4]) - 1];
          p->transform (Transform::scale (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3])));
        } else if (tokens[0] == "tt") {
          Primitive* p = primitives[stoi (tokens[4]) - 1];
          p->transform (Transform::translation (
            stof (tokens[1]),
            stof (tokens[2]),
            stof (tokens[3])));
        }
      }
    }
    file.close();
  }
  for (vector<Primitive*>::iterator it = primitives.begin ();
       it != primitives.end ();
       it++) {
    this->raytracer.addPrimitive (*it);
  }
};

vector<string> split (const string& s, const string& delims) {
  vector<string> tokens;
  size_t pos = s.find_first_not_of (delims);
  while (pos != string::npos) {
    size_t end = s.find_first_of (delims, pos);
    if (end == string::npos)
      tokens.push_back (s.substr (pos));
    else
      tokens.push_back (s.substr (pos, end - pos));
    pos = s.find_first_not_of (delims, end);
  }
  return tokens;
}
