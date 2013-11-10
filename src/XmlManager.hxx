#ifndef GESTUREWRITER_H
#define GESTUREWRITER_H

#include <XnCppWrapper.h>
#include <map>
#include <list>
#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <stdexcept>


#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "IOUtils.hxx"

XERCES_CPP_NAMESPACE_USE
using namespace std;


class XStr
{
    public :
        // -----------------------------------------------------------------------
        //  Constructors and Destructor
        // -----------------------------------------------------------------------
        XStr(const char* const toTranscode){
            // Call the private transcoding method
            fUnicodeForm = XMLString::transcode(toTranscode);
        }

        ~XStr(){
            XMLString::release(&fUnicodeForm);
        }


        // -----------------------------------------------------------------------
        //  Getter methods
        // -----------------------------------------------------------------------
        const XMLCh* unicodeForm() const{
            return fUnicodeForm;
        }

    private :
        // -----------------------------------------------------------------------
        //  Private data members
        //
        //  fUnicodeForm
        //      This is the Unicode XMLCh format of the string.
        // -----------------------------------------------------------------------
        XMLCh*   fUnicodeForm;
};


class XmlManager
{
    #define X(str) XStr(str).unicodeForm()

    public:
        XmlManager();
        virtual ~XmlManager();
        void InitializeDocument(char* DocName);
        void LoadDocument(string filename);
        void SaveDocument(string filename);
        void CloseDocument();
        void Terminate();
        void AddFrameData(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> trackingInfo);
        void WriteGestureData(string gestureType, string focusedHand, list<XnSkeletonJointTransformation> jointQueue);
        void WriteGestureIndexInformation(string gestureType, string focusedHand, XnSkeletonJoint joint, string filename, int startFrameID, int stopFrameID);
        void SetCurrentFrame(int ID);
        void GetFrameByID(int ID);
        void AdvanceFrame();
        void RewindFrame();
        std::map<XnSkeletonJoint,XnSkeletonJointTransformation> GetPositionDataFromCurrentFrame();
        int getMaxAmountOfFrames();
        int getCurrentFrameID();

    protected:
        DOMDocument* doc;
        DOMElement * rootElem;
        DOMElement * currentFrameElem;

        string documentName;
        int CurrentFrame;
        XnSkeletonJointTransformation currentJoint;
        private:

        template <typename T> const char* NumberToString ( T Number )
        {
             return static_cast<ostringstream*>( &(ostringstream() << Number) )->str().c_str();
        }

        void FailAndExit(){
            XMLPlatformUtils::Terminate();
            exit(EXIT_FAILURE);
        }
};

#endif // GESTUREWRITER_H
