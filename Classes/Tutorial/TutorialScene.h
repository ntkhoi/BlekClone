#pragma once 

#include "cocos2d.h"
#include "../LineDrawer/LineDrawer.h"



class TutorialScene : public cocos2d::LayerColor
{
public:

	static  cocos2d::Scene* createTutorialScene();
	virtual bool init();

	virtual void update(float dt);
	CREATE_FUNC(TutorialScene);
	LineDrawer* _linedrawer;

	//cocos2d::Sprite* _sprBalloon;

	void getDataSceneByLevel();
private:
    
    int maxlevel = 10;

	void getcurrentLevel();
	int _cusLevel = 1;
	int _countColision = 0;
	std::vector<cocos2d::Sprite*> _lstcircleSpr;
    std::vector<cocos2d::Sprite*> _lstBlackSpr;
	
	void loadLevelData();
	void addLineDrawer();
	void addCurrentLevel();


	void tutorialSceneRelease();
    void menuVibrateCallback(Ref* pSender);
    void menuSoundCallback(Ref* pSender);
    void reLoadLevel();
    void AddMainMenuLayer();
    void goNextLevel(Ref* psender);
    void goPreLevel( Ref* sender);
    void reloadScene(int);
    void addMenu();
    

    
    
};
