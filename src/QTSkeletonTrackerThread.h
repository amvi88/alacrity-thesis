#ifndef QTSKELETONTRACKERTHREAD_H
#define QTSKELETONTRACKERTHREAD_H

#include "SkeletonTracker.hxx"
#include <XnCppWrapper.h>
#include <QtCore>

class QTSkeletonTrackerThread : public QThread
{
    public:

        QTSkeletonTrackerThread();

        void run();
        void quit();
        void setData(SkeletonTracker * t, std::list<XnSkeletonJoint> j );

    protected:
        SkeletonTracker* tracker;
        std::list<XnSkeletonJoint> joints;

    private:
};

#endif // QTSKELETONTRACKERTHREAD_H
