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
#include "ConfigurationManager.hxx"

using namespace std;
using namespace boost;

class GestureRecognizer{
    private:

    protected:
    ConfigurationManager* mgr = &ConfigurationManager::getInstance();
    XnSkeletonJoint watchSubject;

    public:
    boost::signals2::signal<void (GestureType) > signalGestureDetected;
    list<XnSkeletonJointTransformation> positionList;

    void setObservedJoints(XnSkeletonJoint jointToObserve);
    virtual void registerNewPosition(std::map<XnSkeletonJoint,XnSkeletonJointTransformation>);
    virtual void run();
    virtual void applyAlgorithmToUserInput(list<XnSkeletonJointTransformation> jointQueue);

    virtual void recognizeGesture(list<XnSkeletonJointTransformation> jointList);

};


#endif // GESTURERECOGNIZER_HXX_INCLUDED
