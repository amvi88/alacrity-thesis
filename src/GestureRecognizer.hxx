#ifndef GESTURERECOGNIZER_HXX_INCLUDED
#define GESTURERECOGNIZER_HXX_INCLUDED

#include <queue>
#include <map>
#include <list>
#include <XnCppWrapper.h>
#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time.hpp>
#include "GestureEnumeration.hxx"

#define NUM_SECONDS 2

using namespace std;
using namespace boost;

class GestureRecognizer{
    private:
    XnSkeletonJoint watchSubject;

    public:
    boost::signals2::signal<void (GestureType) > signalGestureDetected;
    list<XnSkeletonJointTransformation> positionList;

    void setObservedJoints(XnSkeletonJoint jointToObserve);
    void registerNewPosition(std::map<XnSkeletonJoint,XnSkeletonJointTransformation>);
    void run();

    virtual void recognizeGesture(list<XnSkeletonJointTransformation> jointList);

};


#endif // GESTURERECOGNIZER_HXX_INCLUDED
