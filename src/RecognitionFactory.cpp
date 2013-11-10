#include "RecognitionFactory.h"

GestureRecognizer* RecognitionFactory::FabricateRecognizer(RecognizerTypeEnum reconType){
    GestureRecognizer * g = 0;
    switch (reconType){
        case DTW:
        break;

        case Bigdelou:
            g = new BigdelouGestureRecognizer();
            break;
        case AngleQuantification:
            g = new AngleQuantificationGestureRecognizer();
            break;
        default:
            break;
    }
    return g;
}
