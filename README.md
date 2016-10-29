# CS 184 Fall 2016
Name: Gavin Song
Platform: OS X
Instructor: James O'Brien

The source code is under /src.

# TO BUILD
1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./as2 [args...]

# USAGE
The program will look for the OBJ file specified by the first argument. Then, the program will produce an output file, named "output.jpg" unless otherwise specified by the second argument.
The camera is assumed to be located at the origin, looking down the -Z axis.
I support a slightly modified version of the OBJ format. The letter "s" followed by four floating point values define a sphere with the given XYZ coordinates and radius, respectively. The letter "c" followed by three floating point values defines a color. The letter "m" followed by three indices and three floats defines a material with Phong component values according to the color indices given and reflection coefficients and anisotropic specular powers according to the given floats. The letters "dl" or "pl" followed by three floats and one color index specifies either a point light or a directional light. "f" and "s" can be followed by an optional fourth index to specify the material.