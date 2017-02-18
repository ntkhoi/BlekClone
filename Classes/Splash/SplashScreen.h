
#ifndef __SplashScene__
#define __SplashScene__

#include <stdio.h>
#include "cocos2d.h"



class SplashScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createSplashScene();

	virtual bool init();
 
	virtual void onEnter();

	void finishSplash(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(SplashScene);
};

#endif /* defined(__stickerPuzzle__SplashScene__) */