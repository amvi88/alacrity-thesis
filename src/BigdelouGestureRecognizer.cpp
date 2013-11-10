#include "BigdelouGestureRecognizer.hxx"

BigdelouGestureRecognizer::BigdelouGestureRecognizer()
{
    //ctor
}

BigdelouGestureRecognizer::~BigdelouGestureRecognizer()
{
    //dtor
}

void BigdelouGestureRecognizer::registerNewPosition(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> jointMap){
   if (jointMap.find(XN_SKEL_TORSO) == jointMap.end()){
        cout << "The torso was not detected, Bigdelou's method requires the Spine (approximated to the torso as OPEN NI doesn't contains it)" << endl;
        return;
   }


    if (jointMap.find(watchSubject) != jointMap.end()){
        XnSkeletonJointTransformation spineRelative = jointMap[watchSubject];
        spineRelative.position.fConfidence = 0.0;
        spineRelative.position.position.X -= jointMap[XN_SKEL_TORSO].position.position.X;
        spineRelative.position.position.Y -= jointMap[XN_SKEL_TORSO].position.position.Y;
        spineRelative.position.position.Z -= jointMap[XN_SKEL_TORSO].position.position.Z;
        positionList.push_back(spineRelative);
    }else{
        cout << "failed getting the articulation info" << endl;
    }
};

void BigdelouGestureRecognizer::recognizeGesture(list<XnSkeletonJointTransformation> jointQueue){
    applyAlgorithmToUserInput(jointQueue);
};

void BigdelouGestureRecognizer::applyAlgorithmToUserInput(list<XnSkeletonJointTransformation> jointQueue){};



