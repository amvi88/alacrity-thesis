#include <iostream>
#include "GestureEnumeration.hxx"
#include "GestureRecognizer.hxx"

void GestureRecognizer::setObservedJoints(XnSkeletonJoint joint){
    //Sets the list of joints that the analyzer is going to inspect
    watchSubject = joint;
}

void GestureRecognizer::registerNewPosition(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> jointMap){
    //Check if the joint we received in the hash is interesting for us ... if it is add it to the queue
    if (jointMap.find(watchSubject) != jointMap.end()){
            positionList.push_back(jointMap[watchSubject]);
    }else{
        cout << "failed getting the articulation info" << endl;
    }
}

void GestureRecognizer::run(){
    while (!xnOSWasKeyboardHit()){
        boost::posix_time::milliseconds workTime(100);
        recognizeGesture(positionList);

        //reduce size to a certain buffer size
        while (positionList.size() > (30 * NUM_SECONDS)){
            positionList.pop_front();
        }

        boost::this_thread::sleep(workTime);
    }
}

void GestureRecognizer::recognizeGesture(list<XnSkeletonJointTransformation> jointQueue){
    XnSkeletonJointTransformation current;
    while (! positionList.empty()){
            current = positionList.front();
            cout << current.position.position.X << ","<< current.position.position.Y << ","<< current.position.position.Z << endl;
            positionList.pop_front();
    }
    signalGestureDetected(NONE);
}
