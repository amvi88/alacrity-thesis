#ifndef XMLGESTURERECOGNIZER_H
#define XMLGESTURERECOGNIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdexcept>
#include <errno.h>


#include "GestureRecognizer.hxx"
#include "XmlManager.hxx"

class XMLGestureRecognizer : public GestureRecognizer
{

    public:
        string handFocus;
        string gesture;

        XmlManager writer;
        XMLGestureRecognizer(string hand);
        virtual ~XMLGestureRecognizer();
        void recognizeGesture(list<XnSkeletonJointTransformation> jointQueue) override;
        void applyAlgorithmToUserInput(list<XnSkeletonJointTransformation> jointQueue) override;
        void saveGesture();

        void LoadFile(){
           struct stat fileStatus;
           errno = 0;
           string filename = handFocus;
           writer.InitializeDocument("Gestures");
           if(stat(filename.c_str(), &fileStatus) == 0) // ==0 ok; ==-1 error
           {
                writer.LoadDocument(filename);
           }
	   }


    protected:
    private:
};

#endif // XMLGESTURERECOGNIZER_H
