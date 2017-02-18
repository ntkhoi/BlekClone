#ifndef XMLREADER
#define XMLREADER


#include "tinyxml2/tinyxml2.h"



#include "cocos2d.h"
#include "SceneData.h"


using namespace tinyxml2;


class XmlReader : public cocos2d::Ref
{
public:
	//static XmlReader *createXmlReader();
	int getCurrentLevel();
	virtual bool init();

	CREATE_FUNC(XmlReader);
	~XmlReader();
	std::vector<SceneData>  getDataSceneByLevel(int);
	tinyxml2::XMLDocument _xmlDoc;

	bool replayCurrentLevel(int);
private:
	
	XMLElement*  getXmlRootElement();
};
#endif
