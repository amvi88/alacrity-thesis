#include "MainWindow.hxx"
#include "GLWidget.hxx"
#include  "SkeletonTracker.hxx"
#include "QTSkeletonTrackerThread.h"


#include <QtGui/QApplication>

using namespace std;
using namespace xn;

SkeletonTracker skeltracker;

ConfigurationManager* mgr;
std::list<XnSkeletonJoint> jointCollection;

void InitializeJointsToTrack(std::list<XnSkeletonJoint>& jointCollection){
    jointCollection.push_front(XN_SKEL_LEFT_HAND);
    jointCollection.push_front(XN_SKEL_RIGHT_HAND);
    jointCollection.push_front(XN_SKEL_HEAD);
    jointCollection.push_front(XN_SKEL_NECK);
    jointCollection.push_front(XN_SKEL_TORSO);
    jointCollection.push_front(XN_SKEL_LEFT_SHOULDER);
	jointCollection.push_front(XN_SKEL_LEFT_ELBOW);
	jointCollection.push_front(XN_SKEL_RIGHT_SHOULDER);
	jointCollection.push_front(XN_SKEL_RIGHT_ELBOW);
	jointCollection.push_front(XN_SKEL_WAIST);
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );

    MainWindow win;

    mgr = &ConfigurationManager::getInstance();
    InitializeJointsToTrack(jointCollection);

    skeltracker.signal.connect(boost::bind( &MainWindow::processNewFrameEvent, &win,  _1));

    QTSkeletonTrackerThread th;
    th.setData(&skeltracker, jointCollection);
    th.start();

    win.assistantThread = &th;
    win.show();

    skeltracker.Finalize();

    return app.exec();
}
