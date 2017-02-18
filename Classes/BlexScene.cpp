#include "BlexScene.h"
#include "CustomDrawNode.h"

USING_NS_CC;

Scene* BlexScene::CreateScene()
{
	auto scene = Scene::create();
	auto myLayer = BlexScene::create();
	scene->addChild(myLayer);
	return scene;
}

bool BlexScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto customDrawNode = CustomDrawNode::create();
	customDrawNode->setPosition(50,50);
	this->addChild(customDrawNode);
	return true;
}
	