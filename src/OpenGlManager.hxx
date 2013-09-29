#ifndef OPENGLMANAGER_HXX_INCLUDED
#define OPENGLMANAGER_HXX_INCLUDED

#include <vector>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Vec3D.hxx"


extern std::vector<Vec3D> JointsToDraw;

const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 1024;
const int SCREEN_FPS    = 60;



bool InitGL();
void Render();
void Update();
void ExecuteMainLoop( int val );

#endif // OPENGLMANAGER_HXX_INCLUDED
