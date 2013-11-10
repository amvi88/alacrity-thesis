#include "AngleQuantificationGestureRecognizer.hxx"

AngleQuantificationGestureRecognizer::AngleQuantificationGestureRecognizer()
{
    //ctor
}

AngleQuantificationGestureRecognizer::~AngleQuantificationGestureRecognizer()
{
    //dtor
}

void AngleQuantificationGestureRecognizer::recognizeGesture(list<XnSkeletonJointTransformation> jointQueue){

    applyAlgorithmToUserInput(jointQueue);



};

void  AngleQuantificationGestureRecognizer::applyAlgorithmToUserInput(list<XnSkeletonJointTransformation> jointQueue){
    XnSkeletonJointTransformation current;
    //Work on the first and second point .. then advance to the second one .. always process one point and the one that follows it
    std::list<XnSkeletonJointTransformation>::iterator next;


    //Array for sectors
    vector<double> characteristicVector(360/mgr->getDegreesPerCircleSector());
    double totalElements;
    for(std::list<XnSkeletonJointTransformation>::iterator current = jointQueue.begin(), penultimate = --jointQueue.end(); current != penultimate; ++current ) {
        next = current;
        ++next;
        characteristicVector[GetSectorNumber(*current , *next, mgr->getDegreesPerCircleSector())]++;
        totalElements++;
    }

    //signalGestureDetected(WAVE_LEFT);
}

float AngleQuantificationGestureRecognizer::GetAngle (XnSkeletonJointTransformation& p1, XnSkeletonJointTransformation& p2){
    float angle = atan2(p2.position.position.Y - p1.position.position.Y, p2.position.position.X - p1.position.position.X);
    if (angle < 0) angle += 2 * M_PI;
    angle *= 180/M_PI;
    return angle;
}


int AngleQuantificationGestureRecognizer::GetSectorNumber(XnSkeletonJointTransformation& p1, XnSkeletonJointTransformation& p2, int degreesPerSector){
    int currentSector = 0;

    float direction = GetAngle(p1, p2);
    //cout << "Angle :" << direction << endl;
    for (float currentAngle = degreesPerSector; currentAngle < 360; currentAngle+=degreesPerSector){
        if (direction <= currentAngle){
            break;
        }
        currentSector++;
    }
    //cout << "Angle :" << direction << " sector : " << currentSector <<endl;
    return currentSector;
}
