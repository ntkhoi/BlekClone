#pragma once
#include "cocos2d.h"


class BlexScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	CREATE_FUNC(BlexScene);
};

