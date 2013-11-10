#include "XMLGestureRecognizer.hxx"

XMLGestureRecognizer::XMLGestureRecognizer(string hand)
{
    handFocus = hand;
    LoadFile();
}

XMLGestureRecognizer::~XMLGestureRecognizer()
{
}


void  XMLGestureRecognizer::recognizeGesture(list<XnSkeletonJointTransformation> jointQueue){

};


void  XMLGestureRecognizer::applyAlgorithmToUserInput(list<XnSkeletonJointTransformation> jointQueue){
    saveGesture();
};

void XMLGestureRecognizer::saveGesture(){
    writer.WriteGestureData(gesture, handFocus, positionList);
    writer.SaveDocument(handFocus);
    writer.CloseDocument();
}
