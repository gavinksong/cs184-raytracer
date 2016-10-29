#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "camera.h"
#include "film.h"
#include "light.h"
#include "material.h"
#include "scene.h"
#include "sphere.h"
#include "triangle.h"
#include "vec3.h"

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265 // Should be used from mathlib

using namespace std;

//****************************************************
// More macros
//****************************************************
#define clampf(x, min, max) (fminf (max, fmaxf (min, x)))

//****************************************************
// Global Variables
//****************************************************
Camera camera (700, 500);
Scene scene (&camera);

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {

    // Set up the scene
    if (argc > 1) {
        scene.readFile (argv[1]);
        Film film = scene.render ();
        if (argc > 2)
            film.writeToJPEG (argv[2]);
        else
            film.writeToJPEG ("output.jpg");
    }

    return 0;
}
