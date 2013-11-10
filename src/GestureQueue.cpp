#include "GestureQueue.h"

GestureQueue::GestureQueue()
{
    config = &ConfigurationManager::getInstance();
};

GestureQueue::~GestureQueue()
{

};


void GestureQueue::Init(){
    LoadDocument();
};


void GestureQueue::Save(){
    xmlManager.SaveDocument(currentFile);
};

void GestureQueue::Finalize(){
    xmlManager.CloseDocument();
};


void GestureQueue::AddGestureEntry(string gestureType, string focusedHand, XnSkeletonJoint joint, string filename, int startFrameID, int stopFrameID){
    xmlManager.WriteGestureIndexInformation(gestureType, focusedHand, joint, filename, startFrameID, stopFrameID);
};

void GestureQueue::LoadDocument(){

    string Path = config->getRecordingDirPath()+string("\/")+config->getIndexFilename();
    string LocalPath = config->getRecordingDirPathLocal()+string("\/")+config->getIndexFilename();
    currentFile = LocalPath;

    if (IOUtils::FileExistsAndNotEmpty(LocalPath)){
        DoBackUp(LocalPath);
        xmlManager.LoadDocument(LocalPath);
    }
    else if (IOUtils::FileExistsAndNotEmpty(Path)){
        currentFile = Path;
        DoBackUp(Path);
        xmlManager.LoadDocument(Path);
    }else{
        xmlManager.InitializeDocument("IdentifiedGestures");
    }
};

void GestureQueue::DoBackUp(string Filepath){
    string BackUpPath = Filepath + string(".bak");
    std::ifstream  src(Filepath.c_str(), std::ios::binary);
    std::ofstream  dst(BackUpPath.c_str(),   std::ios::binary);
    dst << src.rdbuf();

    dst.close();
    src.close();
};

