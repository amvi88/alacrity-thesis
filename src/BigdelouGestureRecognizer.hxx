#ifndef BIGDELOUGESTURERECOGNIZER_H
#define BIGDELOUGESTURERECOGNIZER_H

#include "GestureRecognizer.hxx"

using namespace std;
using namespace boost;

class BigdelouGestureRecognizer : public GestureRecognizer
{
    public:
        BigdelouGestureRecognizer();
        virtual ~BigdelouGestureRecognizer();
        void registerNewPosition(std::map<XnSkeletonJoint,XnSkeletonJointTransformation>) override;
        void recognizeGesture(list<XnSkeletonJointTransformation> jointQueue) override;
        void applyAlgorithmToUserInput(list<XnSkeletonJointTransformation> jointQueue) override;
    protected:
    private:
};

#endif // BIGDELOUGESTURERECOGNIZER_H
