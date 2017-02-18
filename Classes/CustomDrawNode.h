//
//  CustomDrawNode.hpp
//  TestCC01
//
//  Created by Nguyen Tan Loc on 6/13/16.
//
//

#ifndef CustomDrawNode_h
#define CustomDrawNode_h

#include "cocos2d.h"
USING_NS_CC;

#define SEGMENT  100

class CustomDrawNode : public cocos2d::Node
{
public:
    CREATE_FUNC(CustomDrawNode);
    virtual bool init() override;
    void onDraw();
    virtual void update(float dt);
    void updateDraw(float dt);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
private:
    cocos2d::CustomCommand  _renderCommand;
    cocos2d::Sprite *spr;
    cocos2d::Vec2 *listVertex;
    cocos2d::Vec2 *listTexCoord;
    float angle;
    int numDraw;

};

#endif /* CustomDrawNode_hpp */
