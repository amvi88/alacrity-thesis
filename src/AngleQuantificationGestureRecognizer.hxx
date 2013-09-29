#ifndef ANGLEQUANTIFICATIONGESTURERECOGNIZER_H
#define ANGLEQUANTIFICATIONGESTURERECOGNIZER_H

#include "GestureRecognizer.hxx"

using namespace std;
using namespace boost;

class AngleQuantificationGestureRecognizer : public GestureRecognizer
{
    public:
        AngleQuantificationGestureRecognizer();
        virtual ~AngleQuantificationGestureRecognizer();
        void recognizeGesture(list<XnSkeletonJointTransformation> jointQueue) override;
    protected:
        float GetAngle (XnSkeletonJointTransformation& p1, XnSkeletonJointTransformation& p2);
        int  GetSectorNumber(XnSkeletonJointTransformation& p1, XnSkeletonJointTransformation& p2, int degreesPerSector);
    private:
};

#endif // ANGLEQUANTIFICATIONGESTURERECOGNIZER_H
