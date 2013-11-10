#ifndef RECOGNITIONFACTORY_H
#define RECOGNITIONFACTORY_H

#include "GestureRecognizer.hxx"
#include "BigdelouGestureRecognizer.hxx"
#include "AngleQuantificationGestureRecognizer.hxx"
#include "GestureRecognizer.hxx"

enum RecognizerTypeEnum{
    Bigdelou,
    BigdelouHierarchy,
    DTW,
    AngleQuantification,
    Default
};

class RecognitionFactory
{
    public:
        static GestureRecognizer* FabricateRecognizer(RecognizerTypeEnum reconType);
    protected:
    private:
};

#endif // RECOGNITIONFACTORY_H
