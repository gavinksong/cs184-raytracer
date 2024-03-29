  # Original file Copyright CMU462 Fall 2015: 
# Kayvon Fatahalian, Keenan Crane,
# Sky Gao, Bryce Summers, Michael Choquette.
cmake_minimum_required(VERSION 2.8)

# Application source
set(APPLICATION_SOURCE
  camera.cpp
  film.cpp
  light.cpp
  main.cpp
  material.cpp
  primitive.cpp
  raytracer.cpp
  sampler.cpp
  scene.cpp
  sphere.cpp
  transform.cpp
  triangle.cpp
  vec3.cpp
)

#-------------------------------------------------------------------------------
# Set include directories
#-------------------------------------------------------------------------------
include_directories(
  ${GLEW_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${JPEG_INCLUDE_DIRS}
#  ${FREETYPE_INCLUDE_DIRS}
)

#-------------------------------------------------------------------------------
# Set link directories
#-------------------------------------------------------------------------------
link_directories(
  ${GLEW_LIBRARY_DIRS}
  ${GLFW_LIBRARY_DIRS}
  ${JPEG_LIBRARY_DIRS}
#  ${CGL_LIBRARY_DIRS}
#  ${FREETYPE_LIBRARY_DIRS}
)

#-------------------------------------------------------------------------------
# Add executable
#-------------------------------------------------------------------------------
add_executable(as2 ${APPLICATION_SOURCE})

target_link_libraries( as2
    glew ${GLEW_LIBRARIES}
    glfw ${GLFW_LIBRARIES}
    jpeg ${JPEG_LIBRARIES}
    ${OPENGL_LIBRARIES}
#    ${FREETYPE_LIBRARIES}
    ${CMAKE_THREADS_INIT}
)

#-------------------------------------------------------------------------------
# Platform-specific configurations for target
#-------------------------------------------------------------------------------
if(APPLE)
  set_property( TARGET as2 APPEND_STRING PROPERTY COMPILE_FLAGS
                "-Wno-deprecated-declarations -Wno-c++11-extensions")
endif(APPLE)

# Put executable in build directory root
set(EXECUTABLE_OUTPUT_PATH ..)

# Install to project root
install(TARGETS as2 DESTINATION ${Assignment2_SOURCE_DIR})
