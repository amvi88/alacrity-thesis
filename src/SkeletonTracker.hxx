#ifndef SKELETONTRACKER_HXX_INCLUDED
#define SKELETONTRACKER_HXX_INCLUDED
#include <XnCppWrapper.h>
#include <list>



//Call back functions
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator&, XnUserID nId, void*);
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator&, XnUserID nId, void*);
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& , const XnChar* strPose, XnUserID nId, void*);
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& , XnUserID nId, void* );
void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& , XnUserID nId, XnCalibrationStatus eStatus, void*);



class SkeletonTracker{
    private:

    public:
    boost::signals2::signal<void (std::map<XnSkeletonJoint,XnSkeletonJointTransformation>) > signal;
    XnBool fileExists(const char *fn);
    void run(std::list<XnSkeletonJoint>);
    void CheckResult(XnStatus nRetVal, char* what);

    #define CONFIG_XML_PATH "bin/Data/Config.xml"
    #define CONFIG_XML_PATH_LOCAL "Config.xml"
    #define MAX_NUM_USERS 1
};

#endif // SKELETONTRACKER_HXX_INCLUDED
