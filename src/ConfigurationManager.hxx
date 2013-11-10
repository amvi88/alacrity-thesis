#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <map>
#include <stdlib.h>
#include <stdexcept>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class ConfigurationSettings{
    public:

    static const string CONF_XML_PATH;
    static const string CONF_XML_PATH_LOCAL;
    static const string RECORDING_DIR;
    static const string RECORDING_DIR_LOCAL;
    static const string INDEX_FILE;
    static const string MAX_USERS;

    //OPEN GL
    static const string PROJECT_NAME;
    static const string SCREEN_WIDTH ;
    static const string SCREEN_HEIGHT;
    static const string SCREEN_FPS;

    //GESTURE
    static const string MAX_GESTURE_DURATION;
    static const string INTERVAL_FOR_GESTURE_CHECK;

    //
    static const string DEGREES_PER_CIRCLE_SECTOR;

};


class ConfigurationManager
{
    public:
        static ConfigurationManager& getInstance()
        {
            static ConfigurationManager instance;
            instance.initializeSettings();
            return instance;
        }

        //Open GL Variables
        const char* getProjectName();
        int getScreenWidth();
        int getScreenHeight();
        int getFPS();

        //OpenNi
        const char* getOpenNIConfigFilePath();
        const char* getOpenNIConfigFilePathLocal();
        int getMaxUsers();

        int getMaxGestureDuration();
        int getCheckForGestureInterval();
        int getDegreesPerCircleSector();

        //XML Index
        const char* getRecordingDirPath();
        const char* getRecordingDirPathLocal();
        const char* getIndexFilename();

    private:
        ConfigurationManager() {}
        ConfigurationManager(ConfigurationManager const&);
        void operator=(ConfigurationManager const&);

     protected:
        std::map <string, string> ConfigurationValues;
        void initializeSettings();
        int convertStringToInt(string settingName, string settingToconvert);
        string getSetting(string key);
 };


#endif // CONFIGURATIONMANAGER_H
