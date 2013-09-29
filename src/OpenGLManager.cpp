#include "OpenGlManager.hxx"

using namespace std;

bool InitGL(){
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        std::cout <<  "Error initializing OpenGL! " << gluErrorString( error )  << "\n";
        return false;
    }

    return true;
}


void Render(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Update screen
    glutSwapBuffers();
}



void Update(){}

void ExecuteMainLoop( int val )
{
    //Frame logic
    Update();
    Render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, ExecuteMainLoop, val );
}

