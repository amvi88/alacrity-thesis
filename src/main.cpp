#include <iostream>
#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time.hpp>
#include <XnCppWrapper.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "OpenGlManager.hxx"
#include "SkeletonTracker.hxx"
#include "GestureRecognizer.hxx"
#include "GestureEnumeration.hxx"
#include "AngleQuantificationGestureRecognizer.hxx"

using namespace std;
using namespace boost;
using namespace xn;


void actOnGesture(GestureType gesture){
    cout << "Received " << gesture << endl;
};

void InitializeJointsToTrack(std::list<XnSkeletonJoint>& jointCollection){
    jointCollection.push_front(XN_SKEL_LEFT_HAND);
    jointCollection.push_front(XN_SKEL_RIGHT_HAND);
};

int main(int argc, char* args[] ){

    std::list<XnSkeletonJoint> jointCollection;
    InitializeJointsToTrack(jointCollection);
    GestureRecognizer gr;
    AngleQuantificationGestureRecognizer agr;
    SkeletonTracker skeltracker;

    agr.setObservedJoints(XN_SKEL_LEFT_HAND);
    agr.signalGestureDetected.connect(boost::bind( &actOnGesture, _1));

    skeltracker.signal.connect(boost::bind( &GestureRecognizer::registerNewPosition, &agr, _1));

    thread kinectWorker(boost::bind(&SkeletonTracker::run, &skeltracker,_1), jointCollection);
    thread gestureWorker(boost::bind(&GestureRecognizer::run, &agr));


    glutInit( &argc, args );

	//Create OpenGL 2.1 context
	//glutInitContextVersion( 2, 1 );

	//Create Double Buffered Window
	glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "Alacrity" );

	//Do post window/context creation initialization
	if( !InitGL() )
	{
		printf( "Unable to initialize graphics library!\n" );
		return 1;
	}

	//Set rendering function
	glutDisplayFunc( Render );

	//Set main loop
	glutTimerFunc( 1000 / SCREEN_FPS, ExecuteMainLoop, 0 );

	//Start GLUT main loop
	glutMainLoop();

    kinectWorker.join();
    gestureWorker.join();
;
};
