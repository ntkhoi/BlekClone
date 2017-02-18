
#ifndef SCENEDATA
#define SCENEDATA

#include "cocos2d.h"
USING_NS_CC;

enum SCENEDATATYPE
{
	Circlesprite,
	BlockSprite,
};
struct SceneData
{


	SceneData(std::string _fileNam, Vec2 _pos, float _radius, SCENEDATATYPE _sceneDataType,Color3B _color  ) : file_name(_fileNam), pos(_pos), radius(_radius),
    sceneDataType(_sceneDataType), color(_color)
    {
    }
	std::string file_name;
	Vec2 pos;
	float radius;
	SCENEDATATYPE sceneDataType;
    Color3B color;
    

};

#endif