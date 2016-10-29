#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

//include header file for glfw library so that we can use OpenGL
#include <GLFW/glfw3.h>
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
GLfloat translation[3] = {0.0f, 0.0f, 0.0f};
bool auto_strech = false;
Camera camera (700, 500);
Scene scene (&camera);

//****************************************************
// Simple init function
//****************************************************
void initializeRendering()
{
    glfwInit();
}

//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************
void setPixel(float x, float y, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glVertex2f(x+0.5, y+0.5);  // The 0.5 is to target pixel centers
    // Note: Need to check for gap bug on inst machines.
}

//****************************************************
// Keyboard inputs
//****************************************************
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_Q: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
        case GLFW_KEY_LEFT :
            if (action) translation[0] -= 0.01f * camera.width; break;
        case GLFW_KEY_RIGHT:
            if (action) translation[0] += 0.01f * camera.width; break;
        case GLFW_KEY_UP   :
            if (action) translation[1] += 0.01f * camera.height; break;
        case GLFW_KEY_DOWN :
            if (action) translation[1] -= 0.01f * camera.height; break;
        case GLFW_KEY_F:
            if (action) auto_strech = !auto_strech; break;
        default: break;
    }
}

//****************************************************
// Draw the scene.
//****************************************************
void drawScene(void)
{
    glBegin(GL_POINTS);

    Film film = scene.render ();
    for (int i = 0; i < camera.width; i++) {
        for (int j = 0; j < camera.height; j++) {
            Vec3 rgb = film.getColorAt (i, j);
            rgb.x = clampf (rgb.x, 0, 1);
            rgb.y = clampf (rgb.y, 0, 1);
            rgb.z = clampf (rgb.z, 0, 1);
            setPixel(i, camera.height - 1 - j, rgb.x, rgb.y, rgb.z);
        }
    }

    glEnd();
}

//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void display(GLFWwindow* window)
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); //clear background screen to black
    
    glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)
    
    glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"
    
    //----------------------- code to draw objects --------------------------
    glPushMatrix();
    glTranslatef (translation[0], translation[1], translation[2]);
    drawScene ();
    glPopMatrix();
    
    glfwSwapBuffers(window);
}

//****************************************************
// function that is called when window is resized
//***************************************************
void size_callback(GLFWwindow* window, int width, int height)
{
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &camera.width, &camera.height);
    
    glViewport(0, 0, camera.width, camera.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, camera.width, 0, camera.height, 1, -1);
    camera.autoResize ();
    
    display(window);
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {

    //This initializes glfw
    initializeRendering();
    
    GLFWwindow* window = glfwCreateWindow( camera.width, camera.height, "CS184", NULL, NULL );
    if ( !window )
    {
        cerr << "Error on window creating" << endl;
        glfwTerminate();
        return -1;
    }
    
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if ( !mode )
    {
        cerr << "Error on getting monitor" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent( window );
    
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &camera.width, &camera.height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, camera.width, 0, camera.height, 1, -1);
    
    glfwSetWindowTitle(window, "CS184");
    glfwSetWindowSizeCallback(window, size_callback);
    glfwSetKeyCallback(window, key_callback);

    // Set up the scene
    if (argc > 1) {
        scene.readFile (argv[1]);
        Film film = scene.render ();
        if (argc > 2)
            film.writeToJPEG (argv[2]);
        else
            film.writeToJPEG ("output.jpg");
    }

    while( !glfwWindowShouldClose( window ) ) // infinite loop to draw object again and again
    {   // because once object is draw then window is terminated
        display( window );
        
        if (auto_strech){
            glfwSetWindowSize(window, mode->width, mode->height);
            glfwSetWindowPos(window, 0, 0);
        }
        
        glfwPollEvents();
    }

    return 0;
}
