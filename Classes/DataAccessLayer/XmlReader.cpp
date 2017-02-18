

#include "XmlReader.h"
USING_NS_CC;

using namespace tinyxml2;

XmlReader::~XmlReader()
{
    CCLOG("Decontructer");
    
}

bool XmlReader::init()
{
    
    ////    std::string asdfd = FileUtils::getInstance()->fullPathFromRelativeFile("../Resource/bledata.xml", "bledata.xml");
    //	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("bledata.xml");
    //	//FILE* fp = fopen(fullPath.c_str, "w");
    //	CCLOG("LOADING");
    //	if (√(fullPath.c_str()) != XML_SUCCESS)
    //		CCLOG("XML_FALSE");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    Data data = FileUtils::getInstance()->getDataFromFile("bledata.xml");
    
    XMLError error = _xmlDoc.Parse((const char*)data.getBytes());
    if (error != XMLError::XML_SUCCESS)
        CCLOG("Load text xml fail");
    
    
#else
//    Data data = FileUtils::getInstance()->getDataFromFile("bledata.xml");
//    
//    XMLError error = _xmlDoc.Parse((const char*)data.getBytes());
//    if (error != XMLError::XML_SUCCESS)
//        CCLOG("Load text xml fail");
//
    
    
//    Data data = FileUtils::getInstance()->getDataFromFile("bledata.xml");
//    
//    XMLError error = _xmlDoc.Parse((const char*)data.getBytes());
//    if (error != XMLError::XML_SUCCESS)
//        CCLOG("Load text xml fail");
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("bledata.xml");
    if (_xmlDoc.LoadFile(fullPath.c_str()) != XML_SUCCESS)
        CCLOG("Load text xml fail");
     CCLOG("Load text xml Success");
#endif
    
    //
    //    XMLElement *pRoot = _xmlDocument.RootElement();
//    CCLOG("Load text xml Success");
//
    
    return true;
}


int XmlReader::getCurrentLevel()
{
    
    XMLElement* pRoot = _xmlDoc.RootElement();
    CCLOG("Get Type");
    XMLElement *config = pRoot->FirstChildElement("Config");
    if (config != nullptr)
    {
        int cusLevel = config->IntAttribute("curLevel");
        return cusLevel;
    }
    
    return -1;
}

std::vector<SceneData>  XmlReader::getDataSceneByLevel(int nLevel)
{
    std::vector<SceneData> lstSceneData;
    XMLElement* pRoot = _xmlDoc.RootElement();
    XMLElement* lstLevel = pRoot->FirstChildElement("LstLevel");
    if (lstLevel != nullptr)
    {
        XMLElement* child;
        
        for (child = lstLevel->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
        {
            if (child->IntAttribute("id") == nLevel)
            {
                break;
            }
        }
        XMLElement*	Circlesprite = child->FirstChildElement("Circlesprite");
        for (tinyxml2::XMLElement* cirleSpr = Circlesprite->FirstChildElement(); cirleSpr != NULL; cirleSpr = cirleSpr->NextSiblingElement())
        {
            std::string fileName = cirleSpr->Attribute("filename");
            float posX = cirleSpr->FloatAttribute("posX");
            float posY = cirleSpr->FloatAttribute("posY");
            float radius = cirleSpr->FloatAttribute("radius");
            int colorR= cirleSpr->IntAttribute("ColorR");
            int colorG= cirleSpr->IntAttribute("ColorG");
            int colorB= cirleSpr->IntAttribute("ColorB");
            
            
            Color3B color = Color3B(colorR,colorG, colorB);

            Vec2 pos = Vec2(posX, posY);
            lstSceneData.push_back(SceneData(fileName, pos, radius, SCENEDATATYPE::Circlesprite,color));
            
        }
        
        XMLElement*	blacksprite = child->FirstChildElement("blacksprite");
        for (tinyxml2::XMLElement* cirleSpr = blacksprite->FirstChildElement(); cirleSpr != NULL; cirleSpr = cirleSpr->NextSiblingElement())
        {
            std::string fileName = cirleSpr->Attribute("filename");
            float posX = cirleSpr->FloatAttribute("posX");
            float posY = cirleSpr->FloatAttribute("posY");
            float radius = cirleSpr->FloatAttribute("radius");
            Vec2 pos = Vec2(posX, posY);
            lstSceneData.push_back(SceneData(fileName, pos, radius, SCENEDATATYPE::BlockSprite,Color3B::BLACK)  );
        }
    }
    return lstSceneData;
}

bool XmlReader::replayCurrentLevel(int nNextlevel)
{
    XMLElement* pRoot = _xmlDoc.RootElement();
    CCLOG("Get Type");
    XMLElement *config = pRoot->FirstChildElement("Config");
    if (config != nullptr)
    {
        config->SetAttribute("curLevel" ,nNextlevel);
        
    }
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("bledata.xml");
    _xmlDoc.SaveFile(fullPath.c_str());
    return true;
}






