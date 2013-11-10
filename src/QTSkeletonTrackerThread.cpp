#include "QTSkeletonTrackerThread.h"

QTSkeletonTrackerThread::QTSkeletonTrackerThread()
{
    //ctor
}

void QTSkeletonTrackerThread::run(){
    tracker->run(joints);
}

void QTSkeletonTrackerThread::quit(){
    tracker->stopSkeletonTracking();
}

void QTSkeletonTrackerThread::setData(SkeletonTracker* t, std::list<XnSkeletonJoint> j ){
    tracker = t;
    joints  = j;
}
