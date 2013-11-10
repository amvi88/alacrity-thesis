#ifndef SKELETONTRACKER_HXX_INCLUDED
#define SKELETONTRACKER_HXX_INCLUDED
#include <XnCppWrapper.h>
#include <list>
#include "ConfigurationManager.hxx"

#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>

#include <XnCppWrapper.h>


using namespace boost;

extern XnBool g_bNeedPose;
extern XnChar g_strPose[20];
extern xn::Context g_Context;
extern xn::ScriptNode g_scriptNode;
extern xn::DepthGenerator g_DepthGenerator;
extern xn::UserGenerator g_UserGenerator;

//Call back functions
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator&, XnUserID nId, void*);
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator&, XnUserID nId, void*);
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& , const XnChar* strPose, XnUserID nId, void*);
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& , XnUserID nId, void* );
void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& , XnUserID nId, XnCalibrationStatus eStatus, void*);
XnPoint3D* ConvertToDrawablePositions(XnSkeletonJointPosition originJoint, XnSkeletonJointPosition destinationJoint);
XnPoint3D ConvertToDrawablePosition(XnSkeletonJointPosition originJoint);

class SkeletonTracker{
    private:

    public:

    boost::signals2::signal<void (std::map<XnSkeletonJoint,XnSkeletonJointTransformation>) > signal;
    XnBool fileExists(const char *fn);
    void run(std::list<XnSkeletonJoint>);
    void CheckResult(XnStatus nRetVal, char* what);
    void stopSkeletonTracking();
    void Initialize();
    void Finalize();
    protected:
    bool stopWork;

};

#endif // SKELETONTRACKER_HXX_INCLUDED
