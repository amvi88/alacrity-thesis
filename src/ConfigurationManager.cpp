#include "ConfigurationManager.hxx"

using namespace std;

const string ConfigurationSettings::PROJECT_NAME                ="PROJECT_NAME";
const string ConfigurationSettings::SCREEN_WIDTH                ="SCREEN_WIDTH";
const string ConfigurationSettings::SCREEN_HEIGHT               ="SCREEN_HEIGHT";
const string ConfigurationSettings::SCREEN_FPS                  ="SCREEN_FPS";

const string ConfigurationSettings::CONF_XML_PATH               ="CONFIG_XML_PATH";
const string ConfigurationSettings::CONF_XML_PATH_LOCAL         ="CONFIG_XML_PATH_LOCAL";
const string ConfigurationSettings::MAX_USERS                   ="MAX_NUM_USERS";
const string ConfigurationSettings::MAX_GESTURE_DURATION        ="MAX_GESTURE_DURATION";
const string ConfigurationSettings::INTERVAL_FOR_GESTURE_CHECK  ="INTERVAL_FOR_GESTURE_CHECK";
const string ConfigurationSettings::DEGREES_PER_CIRCLE_SECTOR   ="DEGREES_PER_CIRCLE_SECTOR";

const string ConfigurationSettings::RECORDING_DIR               ="RECORDING_DIR";
const string ConfigurationSettings::RECORDING_DIR_LOCAL         ="RECORDING_DIR_LOCAL";
const string ConfigurationSettings::INDEX_FILE                  ="INDEX_FILE";

int ConfigurationManager::convertStringToInt(string settingName, string settingToconvert){
	int result = 0;
	try
	{
		result = atoi(settingToconvert.c_str());
	}
	catch(...)
	{
		cout << "Exception caugth while trying to convert the setting " << settingName << " !" << endl;
		throw;
	}
	return result;
};

string ConfigurationManager::getSetting(string key){
    if (ConfigurationValues.find(key) != ConfigurationValues.end()){
        return ConfigurationValues[key];
    }else{
        throw string("Couldn't find the specified setting '"+key+"' in the configuration");
    }
}


const char* ConfigurationManager::getProjectName(){
    try{
        return getSetting(ConfigurationSettings::PROJECT_NAME).c_str();
    }catch(exception& e){
        cout << "Failed getting the setting '" << ConfigurationSettings::PROJECT_NAME <<"'"<<endl;
    }
};

int   ConfigurationManager::getScreenWidth(){
    try{
        return convertStringToInt(ConfigurationSettings::SCREEN_WIDTH, getSetting(ConfigurationSettings::SCREEN_WIDTH));
    }catch(exception& e){

    }
};

int   ConfigurationManager::getScreenHeight(){
    try{
        return convertStringToInt(ConfigurationSettings::SCREEN_HEIGHT, getSetting(ConfigurationSettings::SCREEN_HEIGHT));
    }catch(exception& e){

    }
};

int   ConfigurationManager::getFPS(){
    try{
        return convertStringToInt(ConfigurationSettings::SCREEN_FPS, getSetting(ConfigurationSettings::SCREEN_FPS));
    }catch(exception& e){

    }
};

const char* ConfigurationManager::getOpenNIConfigFilePath(){
    try{
        return getSetting(ConfigurationSettings::CONF_XML_PATH).c_str();
    }catch(exception& e){

    }
};

const char* ConfigurationManager::getOpenNIConfigFilePathLocal(){
    try{
        return getSetting(ConfigurationSettings::CONF_XML_PATH_LOCAL).c_str();
    }catch(exception& e){

    }
};

const char* ConfigurationManager::getRecordingDirPath(){
    try{
        return getSetting(ConfigurationSettings::RECORDING_DIR).c_str();
    }catch(exception& e){

    }
};

const char* ConfigurationManager::getRecordingDirPathLocal(){
    try{
        return getSetting(ConfigurationSettings::RECORDING_DIR_LOCAL).c_str();
    }catch(exception& e){

    }
};

const char* ConfigurationManager::getIndexFilename(){
    try{
        return getSetting(ConfigurationSettings::INDEX_FILE).c_str();
    }catch(exception& e){

    }
};

int ConfigurationManager::getMaxUsers(){
    try{
        return convertStringToInt(ConfigurationSettings::MAX_USERS, getSetting(ConfigurationSettings::MAX_USERS));
    }catch(exception& e){

    }
};

int ConfigurationManager::getMaxGestureDuration(){
    try{
        return convertStringToInt(ConfigurationSettings::MAX_GESTURE_DURATION, getSetting(ConfigurationSettings::MAX_GESTURE_DURATION));
    }catch(exception& e){

    }
};

int ConfigurationManager::getCheckForGestureInterval(){
    try{
        return convertStringToInt(ConfigurationSettings::INTERVAL_FOR_GESTURE_CHECK, getSetting(ConfigurationSettings::INTERVAL_FOR_GESTURE_CHECK));
    }catch(exception& e){

    }
};

int ConfigurationManager::getDegreesPerCircleSector(){
    try{
        return convertStringToInt(ConfigurationSettings::DEGREES_PER_CIRCLE_SECTOR, getSetting(ConfigurationSettings::DEGREES_PER_CIRCLE_SECTOR));
    }catch(exception& e){
    }
}



void  ConfigurationManager::initializeSettings(){
    string line;
    ifstream file;

    //Try non local path
    file.open("bin/Data/Alacrity.config", std::ifstream::in);
    if(!file.is_open())
    {
        //Try with local path
        file.open("Alacrity.config", std::ifstream::in);
        if(!file.is_open())
        {
            cout << "Couldn't open the configuration file, the system will exit" <<endl;
            exit(1);
        }
    }

    while (getline (file,line))
    {
        uint position;
        //Ignore blank and comment lines
        if (line.empty() || line.find_first_of('#') == 0)
        {
            continue;
        }
        else if ((position = line.find_first_of('=')) != string::npos){
            ConfigurationValues[line.substr(0, position)] = line.substr(position+1);
        }
    }
    file.close();

//    typedef map<string,string>::iterator it_type;
//    for (it_type iter = ConfigurationValues.begin(); iter != ConfigurationValues.end(); ++iter) {
//           cout <<"Key '"<< iter->first <<"' , Value '"<<  iter->second << "'" <<endl;
//    }



};

