#include "XmlManager.hxx"

XmlManager::XmlManager()
{
    try
    {
        XMLPlatformUtils::Initialize();
    }

    catch(const XMLException& toCatch)
    {
        char *pMsg = XMLString::transcode(toCatch.getMessage());
        XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n" << "  Exception message:" << pMsg;
        XMLString::release(&pMsg);
        FailAndExit();
    }
}

XmlManager::~XmlManager()
{
    Terminate();
}

void XmlManager::Terminate(){
    try{
        XMLPlatformUtils::Terminate();
    }catch(const XMLException& toCatch)
    {
        char *pMsg = XMLString::transcode(toCatch.getMessage());
        XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Finalize Operation.\n" << "  Exception message:" << pMsg;
        XMLString::release(&pMsg);
    }

}

void XmlManager::InitializeDocument(char* DocName){
    CurrentFrame = 0;

    DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));
    if (impl == NULL)
    {
        XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }else{
        try{
            doc = impl->createDocument(
                           0,                    // root element namespace URI.
                           X(DocName),         // root element name
                           0);                   // document type object (DTD).

            rootElem = doc->getDocumentElement();
            currentFrameElem = NULL;
        }
        catch (const OutOfMemoryException&){
            XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
            FailAndExit();
        }
        catch (const DOMException& e){
            XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
            FailAndExit();
        }
    }
}

void XmlManager::AddFrameData(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> trackingInfo){
    try{
        XnSkeletonJoint current;

        DOMElement*  frameElem = doc->createElement(X("Frame"));
        rootElem->appendChild(frameElem);
        frameElem->setAttribute(X("id"), X(NumberToString(CurrentFrame)));

        for (std::map<XnSkeletonJoint,XnSkeletonJointTransformation>::iterator it=trackingInfo.begin(); it != trackingInfo.end(); ++it){
            current = (*it).first;
            currentJoint = (*it).second;

            DOMElement*  jointElem = doc->createElement(X("JointInfo"));
            frameElem->appendChild(jointElem);

            jointElem->setAttribute(X("Joint"), X(NumberToString(current)));
            jointElem->setAttribute(X("X"),     X(NumberToString(currentJoint.position.position.X)));
            jointElem->setAttribute(X("Y"),     X(NumberToString(currentJoint.position.position.Y)));
            jointElem->setAttribute(X("Z"),     X(NumberToString(currentJoint.position.position.Z)));

        }
        CurrentFrame++;

    }
    catch (const OutOfMemoryException&){
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }
    catch (const DOMException& e){
        XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }
    catch (...){

    }

}


void XmlManager::WriteGestureData(string gestureType, string focusedHand, list<XnSkeletonJointTransformation> jointQueue){
    try{

        if (rootElem == 0){
            rootElem = doc->getDocumentElement();
        }


        DOMElement*  frameElem = doc->createElement(X("GestureInstance"));
        rootElem->appendChild(frameElem);

        frameElem->setAttribute(X("GestureType"), X(gestureType.c_str()));
        frameElem->setAttribute(X("Hand"), X(focusedHand.c_str()));


        XnSkeletonJointTransformation current;

        for (std::list<XnSkeletonJointTransformation>::iterator it=jointQueue.begin(); it != jointQueue.end(); ++it){
            current = (*it);

            DOMElement*  pointElem = doc->createElement(X("Point"));
            frameElem->appendChild(pointElem);

            pointElem->setAttribute(X("X"), X(NumberToString(current.position.position.X)));
            pointElem->setAttribute(X("Y"), X(NumberToString(current.position.position.Y)));
            pointElem->setAttribute(X("Z"), X(NumberToString(current.position.position.Z)));
        }
    }
    catch (const OutOfMemoryException&){
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }
    catch (const DOMException& e){
        XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }
    catch (...){

    }
}


void XmlManager::WriteGestureIndexInformation(string gestureType, string focusedHand, XnSkeletonJoint joint, string filename, int startFrameID, int stopFrameID){
    try{

        if (rootElem == 0){
            rootElem = doc->getDocumentElement();
        }

        DOMElement*  frameElem = doc->createElement(X("GestureData"));
        rootElem->appendChild(frameElem);

        frameElem->setAttribute(X("GestureType"), X(gestureType.c_str()));
        frameElem->setAttribute(X("Hand"), X(focusedHand.c_str()));
        frameElem->setAttribute(X("JointID"), X(NumberToString(joint)));
        frameElem->setAttribute(X("StartFrame"), X(NumberToString(startFrameID)));
        frameElem->setAttribute(X("StopFrame"), X(NumberToString(stopFrameID)));
        frameElem->setAttribute(X("Filename"), X(filename.c_str()));

    }
    catch (const OutOfMemoryException&){
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }
    catch (const DOMException& e){
        XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
        FailAndExit();
    }
    catch (...){

    }
}

void XmlManager::SaveDocument(string filename){
        try
        {
            // get a serializer, an instance of DOMLSSerializer
            XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
            DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
            DOMLSSerializer   *theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
            DOMLSOutput       *theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput();

            theOutputDesc->setEncoding(X("UTF-8"));

            XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(X(filename.c_str()));
            theOutputDesc->setByteStream(myFormTarget);

            bool result = theSerializer->write(doc, theOutputDesc);

            if (! result){
                cerr << "Unable to serialize to file " << filename << endl;
            }



            theOutputDesc->release();
            theSerializer->release();
        }
        catch (const OutOfMemoryException&)
        {
            cerr << "OutOfMemoryException" << endl;
            FailAndExit();
        }
        catch (XMLException& e)
        {
            cerr << "An error occurred during creation of output transcoder. Msg is:"  << endl << XMLString::transcode(e.getMessage()) << endl;
            FailAndExit();
        }

}

void XmlManager::LoadDocument(string filename){
        try{
            IOUtils::ValidateFileStatus(filename);
        }
        catch(const std::runtime_error& e)
        {
            cerr << "An error while loading the file. Msg is:"  << e.what() << endl;
        }
        catch(...){}



	   // Configure DOM parser.
       XercesDOMParser* fileParser = new XercesDOMParser;
	   fileParser->setValidationScheme( XercesDOMParser::Val_Never );
	   fileParser->setDoNamespaces( false );
	   fileParser->setDoSchema( false );
	   fileParser->setLoadExternalDTD( false );

	   try
	   {
	      fileParser->parse( X(filename.c_str()));

	      // no need to free this pointer - owned by the parent parser object
	      doc = fileParser->getDocument();
          rootElem = doc->getDocumentElement();
      }
      catch (XMLException& e)
      {
            cerr << "An error occurred while parsing the file. Msg is:"  << endl << XMLString::transcode(e.getMessage()) << endl;
            FailAndExit();
      }
}

void XmlManager::CloseDocument(){
    try{
        doc->release();
    }
    catch (XMLException& e)
    {
        cerr << "An error occurred when closing the document. Msg is:"  << endl << XMLString::transcode(e.getMessage()) << endl;
    }
}

void XmlManager::GetFrameByID(int ID){
    string xPathExp;
    try{
        //xPathExp = "/UserTracking/Frame[@id=\"";
        //xPathExp.append(NumberToString(ID));
        //xPathExp.append("\"]");

        xPathExp = "/UserTracking/Frame[@id='1']";

        DOMXPathResult* result=doc->evaluate(X(xPathExp.c_str()), // "/abc/def/text()[0]"
        rootElem,
        NULL,
        DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE, //DOMXPathResult::ANY_UNORDERED_NODE_TYPE, //DOMXPathResult::STRING_TYPE,
        NULL);

        // look into the xpart evaluate result
        result->snapshotItem(0);
        cout<< XMLString::transcode(result->getNodeValue()->getAttributes()->getNamedItem(X("id"))->getTextContent() )  << endl;
    }
    catch(const DOMXPathException& e){
        cerr << "An error occurred during processing of the XPath expression '" << xPathExp <<  "'. Msg is:" << XMLString::transcode(e.getMessage()) << endl;
        FailAndExit();
    }
    catch(const DOMException& e){
        cerr << "An error occurred during processing of the XPath expression. Msg is:" << XMLString::transcode(e.getMessage()) << endl;
        FailAndExit();
    }
}

void XmlManager::SetCurrentFrame(int ID){
    try{
        if (rootElem->getChildElementCount() <= ID){
            throw new std::runtime_error("The specified frame is invalid, unable to advanced to specified frame");
        }

        if (! currentFrameElem){
            currentFrameElem = rootElem->getFirstElementChild();
        }

        int currentFrameID = atoi(XMLString::transcode(currentFrameElem->getAttribute(X("id"))));
        if (currentFrameID > ID){
            currentFrameElem = rootElem->getFirstElementChild();
        }

        for (int index = 0; index < (ID - currentFrameID) ;index++){
            currentFrameElem = currentFrameElem->getNextElementSibling();
        }
    }
    catch(const std::runtime_error& e){
            cerr << "An error while loading the file. Msg is:"  << e.what() << endl;
    }
    catch(const DOMException& e){
        cerr << "An error occurred while getting the next frame. Msg is:" << XMLString::transcode(e.getMessage()) << endl;
        FailAndExit();
    }catch(...){
            cerr << "There was an error when setting the frame " << ID << endl;
    }
}

void XmlManager::AdvanceFrame(){
    try{
        if (currentFrameElem != 0){
            currentFrameElem = currentFrameElem->getNextElementSibling();
        }
    }
    catch(const DOMException& e){
        cerr << "An error occurred while getting the next frame. Msg is:" << XMLString::transcode(e.getMessage()) << endl;
        FailAndExit();
    }
}

void XmlManager::RewindFrame(){
    try{
        if (currentFrameElem != 0){
            currentFrameElem = currentFrameElem->getPreviousElementSibling();
        }
    }
    catch(const DOMException& e){
        cerr << "An error occurred while getting the previous frame. Msg is:" << XMLString::transcode(e.getMessage()) << endl;
        FailAndExit();
    }
}

map<XnSkeletonJoint,XnSkeletonJointTransformation> XmlManager::GetPositionDataFromCurrentFrame(){
    map<XnSkeletonJoint,XnSkeletonJointTransformation> frameData;
    DOMElement * jointData;
    try {
        if (currentFrameElem){
            string nodeName, Joint, X, Y , Z;
            DOMNode * current_node = NULL;
            DOMElement* current_element = NULL;

            XnSkeletonJointTransformation currentTransform;

            DOMNodeIterator * walker = doc->createNodeIterator(currentFrameElem,DOMNodeFilter::SHOW_ALL ,NULL,true);
            for (current_node = walker->nextNode(); current_node != 0; current_node = walker->nextNode()) {
                current_element = dynamic_cast<DOMElement*>(current_node);
                nodeName = XMLString::transcode(current_element->getTagName());
                if( nodeName == "JointInfo"){
                    Joint = XMLString::transcode(current_element->getAttribute(X("Joint")));
                    X = XMLString::transcode(current_element->getAttribute(X("X")));
                    Y = XMLString::transcode(current_element->getAttribute(X("Y")));
                    Z = XMLString::transcode(current_element->getAttribute(X("Z")));

                    currentTransform.position.position.X = atof (X.c_str());
                    currentTransform.position.position.Y = atof (Y.c_str());
                    currentTransform.position.position.Z = atof (Z.c_str());
                    frameData[(XnSkeletonJoint) atoi(Joint.c_str())] = currentTransform;
                }
            }
         }
    }catch(const DOMException& e){
        cerr << "An error ocurred while transforming the XML to the data. Msg is:" << XMLString::transcode(e.getMessage()) << endl;
        FailAndExit();
    }
    return frameData;
}

int XmlManager::getMaxAmountOfFrames(){
    return (!rootElem) ? 0 : (int) rootElem->getChildElementCount();
}

int XmlManager::getCurrentFrameID(){
    return (!currentFrameElem)? -1 : atoi(XMLString::transcode(currentFrameElem->getAttribute(X("id"))));
}
