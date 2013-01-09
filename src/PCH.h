

// STL

#include <vector>
#include <limits>
#include <cmath>


// BOOST

#include <boost/foreach.hpp>


// GLM

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/ext.hpp>


// GLUT

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/freeglut.h>
#endif

enum TAxis
{
    AXIS_X, AXIS_Y, AXIS_Z
};
