#ifndef GESTUREQUEUE_H
#define GESTUREQUEUE_H

#include <string.h>
#include <list>
#include <XnCppWrapper.h>

#include "XmlManager.hxx"
#include "GestureRecognizer.hxx"
#include "ConfigurationManager.hxx"

class RecordingInfo{
    string FocusedJoint;
    XnSkeletonJoint JointID;
    string GestureType;
    int    StartFrameID;
    int    StopFrameID;
};


class GestureQueue
{
    public:
        GestureQueue();
        virtual ~GestureQueue();
        void Init();
        void AddGestureEntry(string gestureType, string focusedHand, XnSkeletonJoint joint, string filename, int startFrameID, int stopFrameID);
        void Finalize();
        void Save();
    protected:
        void LoadDocument();
        void DoBackUp(string FileName);
    private:
        string currentFile;
        ConfigurationManager * config;
        XmlManager xmlManager;

};

#endif // GESTUREQUEUE_H
