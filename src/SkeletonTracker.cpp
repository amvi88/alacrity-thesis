
#include <iostream>
#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
///Based on Open NI 1.X Alpha Code

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <GL/glut.h>
#include <math.h>
#include <boost/date_time.hpp>
#include "SkeletonTracker.hxx"

//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------
using namespace std;
using namespace boost;

//Global Variables
XnBool g_bNeedPose;
XnChar g_strPose[20];
xn::Context g_Context;
xn::ScriptNode g_scriptNode;
xn::DepthGenerator g_DepthGenerator;
xn::UserGenerator g_UserGenerator;


XnPoint3D* ConvertToDrawablePositions(XnSkeletonJointPosition originJoint, XnSkeletonJointPosition destinationJoint)
{
    XnPoint3D pt[2];
    pt[0] = originJoint.position;
    pt[1] = destinationJoint.position;

    g_DepthGenerator.ConvertRealWorldToProjective(2,pt, pt);
    return pt;
}

XnPoint3D ConvertToDrawablePosition(XnSkeletonJointPosition originJoint)
{
    XnPoint3D pt[1];
    pt[0] = originJoint.position;
    g_DepthGenerator.ConvertRealWorldToProjective(1,pt, pt);
    return pt[0];
}

XnBool SkeletonTracker::fileExists(const char *fn)
{
        XnBool exists;
        xnOSDoesFileExist(fn, &exists);
        return exists;
}

// Callback: New user was detected
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/)
{
        XnUInt32 epochTime = 0;
        xnOSGetEpochTime(&epochTime);
        printf("%d New User %d\n", epochTime, nId);
        // New user found
        if (g_bNeedPose)
        {
            g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
        }
        else
        {
            g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
        }
}

// Callback: An existing user was lost
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& /*generator*/, XnUserID nId, void* /*pCookie*/)
{
        XnUInt32 epochTime = 0;
        xnOSGetEpochTime(&epochTime);
        printf("%d Lost user %d\n", epochTime, nId);
}

// Callback: Detected a pose
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& /*capability*/, const XnChar* strPose, XnUserID nId, void* /*pCookie*/)
{
        XnUInt32 epochTime = 0;
        xnOSGetEpochTime(&epochTime);
        printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
        g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
        g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}

// Callback: Started calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& /*capability*/, XnUserID nId, void* /*pCookie*/)
{
        XnUInt32 epochTime = 0;
        xnOSGetEpochTime(&epochTime);
        printf("%d Calibration started for user %d\n", epochTime, nId);
}

void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& /*capability*/, XnUserID nId, XnCalibrationStatus eStatus, void* /*pCookie*/)
{
        XnUInt32 epochTime = 0;
        xnOSGetEpochTime(&epochTime);
        if (eStatus == XN_CALIBRATION_STATUS_OK)
        {
            // Calibration succeeded
            printf("%d Calibration complete, start tracking user %d\n", epochTime, nId);
            g_UserGenerator.GetSkeletonCap().StartTracking(nId);
        }
        else
        {
            // Calibration failed
            printf("%d Calibration failed for user %d\n", epochTime, nId);
            if(eStatus==XN_CALIBRATION_STATUS_MANUAL_ABORT)
            {
                printf("Manual abort occured, stop attempting to calibrate!");
                return;
            }
            if (g_bNeedPose)
            {
                g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
            }
            else
            {
                g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
            }
        }
}

void SkeletonTracker::CheckResult(XnStatus nRetVal, char* errMsg){
    if (nRetVal != XN_STATUS_OK)
    {
        printf("%s failed: %s\n", errMsg, xnGetStatusString(nRetVal));
        return;
    }
}

void SkeletonTracker::stopSkeletonTracking(){
    stopWork = true;
}

void SkeletonTracker::Initialize(){
    try{
        ConfigurationManager* mgr = &ConfigurationManager::getInstance();

        XnStatus nRetVal = XN_STATUS_OK;
        xn::EnumerationErrors errors;

        const char *fn = NULL;
        if    (fileExists(mgr->getOpenNIConfigFilePath())) fn = mgr->getOpenNIConfigFilePath();
        else if (fileExists(mgr->getOpenNIConfigFilePathLocal())) fn = mgr->getOpenNIConfigFilePathLocal();
        else {
            printf("Could not find '%s' nor '%s'. Aborting.\n" , mgr->getOpenNIConfigFilePath(), mgr->getOpenNIConfigFilePathLocal());
            //return XN_STATUS_ERROR;
            return;
        }
        printf("Reading config from: '%s'\n", fn);

        nRetVal = g_Context.InitFromXmlFile(fn, g_scriptNode, &errors);
        if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
        {
            XnChar strError[1024];
            errors.ToString(strError, 1024);
            printf("%s\n", strError);
            //return (nRetVal);
            return;
        }
        else if (nRetVal != XN_STATUS_OK)
        {
            printf("Open failed: %s\n", xnGetStatusString(nRetVal));
            //return (nRetVal);
            return;
        }

        nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
        CheckResult(nRetVal,"No depth");

        nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
        if (nRetVal != XN_STATUS_OK)
        {
            nRetVal = g_UserGenerator.Create(g_Context);
            CheckResult(nRetVal, "Find user generator");
        }

        XnCallbackHandle hUserCallbacks, hCalibrationStart, hCalibrationComplete, hPoseDetected;
        if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
        {
            printf("Supplied user generator doesn't support skeleton\n");
            //return 1;
            return;
        }
        nRetVal = g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
        CheckResult(nRetVal, "Register to user callbacks");
        nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationStart(UserCalibration_CalibrationStart, NULL, hCalibrationStart);
        CheckResult(nRetVal, "Register to calibration start");
        nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationComplete(UserCalibration_CalibrationComplete, NULL, hCalibrationComplete);
        CheckResult(nRetVal, "Register to calibration complete");

        if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
        {
            g_bNeedPose = TRUE;
            if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
            {
                printf("Pose required, but not supported\n");
                //return 1;
                return;
            }
            nRetVal = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseDetected(UserPose_PoseDetected, NULL, hPoseDetected);
            CheckResult(nRetVal, "Register to Pose Detected");
            g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
        }

        g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

        nRetVal = g_Context.StartGeneratingAll();
        CheckResult(nRetVal, "StartGenerating");

        printf("Starting to run\n");
        if(g_bNeedPose)
        {
            printf("Assume calibration pose\n");
        }
    }
    catch(...){
        cerr << "There was an error while initializing the Skeleton tracker, the application will exit" << endl;
        exit(EXIT_FAILURE);
    }

}

void SkeletonTracker::Finalize(){
    g_scriptNode.Release();
    g_DepthGenerator.Release();
    g_UserGenerator.Release();
    g_Context.Release();
}


void SkeletonTracker::run(std::list<XnSkeletonJoint> jointsToTrack)
{
        Initialize();
        ConfigurationManager* mgr = &ConfigurationManager::getInstance();

        XnUserID aUsers[mgr->getMaxUsers()];
        XnUInt16 nUsers;
        XnSkeletonJointTransformation currentJoint;

        std:map<XnSkeletonJoint,XnSkeletonJointTransformation> jointMap;

        while (!stopWork)
        {
            g_Context.WaitOneUpdateAll(g_UserGenerator);
            // print the torso information for the first user already tracking
            nUsers=mgr->getMaxUsers();
            g_UserGenerator.GetUsers(aUsers, nUsers);
            for(XnUInt16 i=0; i<nUsers; i++)
            {
                if(g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i])==FALSE)
                    continue;

                for (std::list<XnSkeletonJoint>::iterator it=jointsToTrack.begin(); it!=jointsToTrack.end(); ++it){
                    g_UserGenerator.GetSkeletonCap().GetSkeletonJoint(aUsers[i],*it,currentJoint);
                    jointMap[*it]=currentJoint;

                }
                signal(jointMap);

            }

        }
};
