#include "SplashScreen.h"
//#include "Tutorial/TutorialScene.h"
#include "../Tutorial/TutorialScene.h"


#include "HelloWorldScene.h"

USING_NS_CC;

Scene* SplashScene::createSplashScene()
{
	auto splashScene = Scene::create();
	auto layer = SplashScene::create();
	splashScene->addChild(layer);

	return splashScene;
}


bool SplashScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto sprite = Sprite::create("splash.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
    
    
    
    UserDefault::getInstance()->setIntegerForKey("cusLevel", 1);

	return true;
}


void SplashScene::onEnter() {
	Layer::onEnter();
	this->scheduleOnce(schedule_selector(SplashScene::finishSplash), 1.0f);
}

void SplashScene::finishSplash(float dt) {
    Director::getInstance()-> replaceScene(TransitionFade::create(2, TutorialScene::createTutorialScene(), Color3B(255, 255, 255)));
}