#include "TutorialScene.h"


#include "../DataAccessLayer/XmlReader.h"

#include "../DataAccessLayer/SceneData.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;



Scene* TutorialScene::createTutorialScene()
{
    auto scene = Scene::create();
    auto layer = TutorialScene::create();
    scene->addChild(layer);
    return scene;
}

bool TutorialScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    addLineDrawer();
    loadLevelData();
    AddMainMenuLayer();
    
    _countColision = 0 ;
    addMenu();
    
    return true;
}






void TutorialScene::goPreLevel( Ref* sender)
{
    if(_cusLevel == 1 )
        return;
    
    _cusLevel += -1;
    reloadScene(_cusLevel);
    
}

void TutorialScene::goNextLevel( Ref* sender)
{
    
    if(_cusLevel == maxlevel )
        return;
    _cusLevel += 1;
    reloadScene(_cusLevel);
}






void TutorialScene::reLoadLevel()
{
    
    
    
    
    CCLOG(" addLineDrawer();");
    addLineDrawer();
    //	getcurrentLevel();
    CCLOG(" loadLevelData();");
    _countColision = 0 ;
    this->scheduleUpdate();
    loadLevelData();
    
    
    addMenu();
    
    
}


void TutorialScene::addMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto  menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    
    
    //    MenuItemSprite* soundmenu = MenuItemSprite::create(sprVolume, sprVolume,  CC_CALLBACK_1(TutorialScene::menuSoundCallback, this));
    
    MenuItemSprite* preMenu = MenuItemSprite::create(Sprite::create("pre.png") , Sprite::create("pre.png"),  CC_CALLBACK_1(TutorialScene::goPreLevel, this));
    
    
    preMenu->setPosition(30,40);
    menu->addChild(preMenu);
    
    
    MenuItemSprite* nextMenu = MenuItemSprite::create(Sprite::create("next.png"), Sprite::create("next.png"),CC_CALLBACK_1(TutorialScene::goNextLevel, this));
    nextMenu ->setPosition(visibleSize.width - 30 , 40);
    menu->addChild(nextMenu);
    
    
    
    this->addChild(menu);
}



void TutorialScene::AddMainMenuLayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto mainMenuLayer = Layer::create();
    
    Label* tittleLable = Label::createWithSystemFont("Ble Clone","roboto", 30.0f);
    tittleLable->setColor(Color3B(0,0,0));
    tittleLable->setPosition(visibleSize.width/2 , visibleSize.height - 20);
    mainMenuLayer->addChild(tittleLable);
    
    Label* tabPlayLable = Label::createWithSystemFont("Tab to play","roboto", 15.0f);
    tabPlayLable->setColor(Color3B(0,0,0));
    tabPlayLable->setPosition(visibleSize.width/2 , visibleSize.height/2 + 10) ;
    mainMenuLayer->addChild(tabPlayLable);
    
    
    
    
    const std::string UNPRESSED = (!UserDefault::getInstance()->getBoolForKey("ISSOUNDMUTE", false)) ? "iconVolume.png" : "iconmute.png";
    const std::string PRESSED = (!UserDefault::getInstance()->getBoolForKey("ISSOUNDMUTE", false)) ? "iconVolume.png" : "iconmute.png";
    
    
    
    
    
    auto sprVolume = Sprite::create(PRESSED);
    auto sprVibrate = Sprite::create("vibrate.png");
    
    auto  menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    
    
    MenuItemSprite* soundmenu = MenuItemSprite::create(sprVolume, sprVolume,  CC_CALLBACK_1(TutorialScene::menuSoundCallback, this));
    soundmenu->setPosition(50  , visibleSize.height -40 );
    soundmenu->setScale(0.75f);
    menu->addChild(soundmenu);
    
    MenuItemSprite* vibratemenu = MenuItemSprite::create(sprVibrate, sprVibrate ,   CC_CALLBACK_1(TutorialScene::menuVibrateCallback, this));
    vibratemenu->setPosition(50,  visibleSize.height - 120 );
    vibratemenu->setScale(0.75f);
    menu->addChild(vibratemenu);
    
    mainMenuLayer->addChild(menu);
    
    
    
    this->addChild(mainMenuLayer);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    
    
    listener1->onTouchBegan = [&, mainMenuLayer, listener1](Touch* touch, Event* event)
    {
        auto moveby = MoveBy::create(2, Vec2(-300,0));
        auto hide = Hide::create();
        
        auto seq = Sequence::create(moveby, hide,  nullptr);
        
        mainMenuLayer->runAction(seq);
        _eventDispatcher->removeEventListener(listener1);
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
}





void TutorialScene::menuVibrateCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void TutorialScene::menuSoundCallback(Ref* pSender)
{
    
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if(audio->isBackgroundMusicPlaying())
    {
        audio->pauseAllEffects();
        audio->pauseBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey("ISSOUNDMUTE", true);
    }
    else{
        audio->resumeAllEffects();
        audio->resumeBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey("ISSOUNDMUTE", false);
        
    }
    
    
    
    // Cast the reference into a MenuItem so we can use its methods.
    auto  BUTTON = dynamic_cast<MenuItemSprite*>(pSender);
    if (!BUTTON) {return;}
    
    
    
    
    // Whether or not its muted will determine the graphics. I'm assuming something like a toggle switch here but you can be simpler like with your 2 previous graphics of course.
    const std::string UNPRESSED = (audio->isBackgroundMusicPlaying()) ? "iconVolume.png" : "iconmute.png";
    const std::string PRESSED = (audio->isBackgroundMusicPlaying()) ? "iconVolume.png" : "iconmute.png";
    
    
    BUTTON->setSelectedImage(Sprite::create(UNPRESSED));
    BUTTON->setNormalImage(Sprite::create(PRESSED));
    
    
}



void TutorialScene::update(float dt)
{
    
    
    
    if (_linedrawer->isResetDrawLine)
    {
        _countColision = 0;
        for (Sprite* sprite : _lstcircleSpr)
        {
            sprite->removeFromParent();
        }
        loadLevelData();
        _linedrawer->isResetDrawLine = false;
        return;
    }
    
    if(!_lstBlackSpr.empty())
    {
        for(int i = 0 ; i != _lstBlackSpr.size() ; i++)
        {
            Sprite* blackSpr = _lstBlackSpr[i];
            if( _linedrawer->iscollision(blackSpr))
            {
                _countColision = 0;
                _linedrawer->_isColissionBlackSpr = true;
            }
        }
    }
    
    if (!_lstcircleSpr.empty())
    {
        for (int i = 0; i != _lstcircleSpr.size(); i++)
        {
            Sprite *sprite = _lstcircleSpr[i];
            if (_linedrawer->iscollision(sprite))
            {
                _linedrawer-> _isColissionBlueSpr = true;
                ++_countColision;
                
                // vibrate in IOS
                //                Device::vibrate(500);
                
                CCLOG("_countColision : %d" , _countColision);
                CCLOG("i : %d" , i);
                auto fadeout = FadeOut::create(1.0f);
                auto scaleby = ScaleBy::create(1.0f, 3.0f);
                auto mySpawn = Spawn::create(fadeout, scaleby, nullptr);
                sprite->runAction(mySpawn);
                
                sprite->setPosition(-500,-500);
                
                
                if (_countColision == _lstcircleSpr.size())
                {
                    _cusLevel++;
                    reloadScene(_cusLevel);
                    
                    
                    break;
                    
                }
            }
        }
    }
}



void TutorialScene::reloadScene(int nSceneLevel)
{
    _countColision = 0 ;
    
    unscheduleUpdate();
    CCLOG("unscheduleUpdate()");
    
    stopAllActions();
    CCLOG("Stop all action");
    this->removeAllChildren();
    _lstcircleSpr.clear();
    
    
    cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
    
    
    UserDefault::getInstance()->setIntegerForKey("cusLevel", nSceneLevel);
    Label* lbSceneLevel = Label::createWithSystemFont(StringUtils::format("%i", _cusLevel), "roboto", 18.0f );
    auto visibleSize = Director::getInstance()->getVisibleSize();
    lbSceneLevel->setPosition(visibleSize.width /2 , visibleSize.height/2 ) ;
    lbSceneLevel->setColor(Color3B(128,128,128));
    this-> addChild(lbSceneLevel);
    auto scaleby = ScaleBy::create(1.0f, 3.0f);
    
    auto hide = Hide::create();
    CallFunc* initcalback =   CallFunc::create(CC_CALLBACK_0(TutorialScene::reLoadLevel, this));
    lbSceneLevel->runAction(Sequence::create(scaleby, hide, initcalback, nullptr));
    CCLOG("reload level");
}

void TutorialScene::addLineDrawer()
{
    _linedrawer = LineDrawer::create();
    this->addChild(_linedrawer);
}

void TutorialScene::loadLevelData()
{
    
    XmlReader * objXmlReader = XmlReader::create();
    CCLOG(" XmlReader * objXmlReader = XmlReader::create();");
    _lstcircleSpr.clear();
    _lstBlackSpr.clear();
    
    int currenelevel = UserDefault::getInstance()->getIntegerForKey("cusLevel", 1);
    
    auto lstSprite = objXmlReader->getDataSceneByLevel(currenelevel);
    
    for (SceneData scenedata : lstSprite)
    {
        Sprite* sprite = Sprite::create(scenedata.file_name);
        sprite->setPosition(scenedata.pos);
        sprite->setColor(scenedata.color);
        sprite->setScale((float)(scenedata.radius) / sprite->getContentSize().width);
        
        if (scenedata.sceneDataType == SCENEDATATYPE::Circlesprite)
        {
            _lstcircleSpr.push_back(sprite);
        }
        if(scenedata.sceneDataType == SCENEDATATYPE::BlockSprite)
        {
            
            sprite->setColor(Color3B::BLACK);
            _lstBlackSpr.push_back(sprite);
        }
        this->addChild(sprite);
    }
    
}

void TutorialScene::addCurrentLevel()
{
    _cusLevel++;
    UserDefault::getInstance()->setIntegerForKey("cusLevel", _cusLevel);
    
}



void TutorialScene::tutorialSceneRelease()
{
    cleanup();
    //this->remove();
    /*this->removeAllChildren();*/
    if (_linedrawer != nullptr)
    {
        _linedrawer->release();
    }
    _lstcircleSpr.clear();
    init();
    
};


