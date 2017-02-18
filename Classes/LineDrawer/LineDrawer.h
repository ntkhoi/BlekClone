#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define SEGMENT  100

class LineDrawer : public cocos2d::Node
{
public:

	~LineDrawer();

    bool  isResetDrawLine ;
    bool _isColissionBlackSpr = false;
    bool _isColissionBlueSpr = false;


	virtual bool init() ;
	CREATE_FUNC(LineDrawer);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	void onDraw();
	virtual void update(float dt);
	bool iscollision(cocos2d::Sprite* sprite);
	
private:

	void drawLineTexture(Renderer *renderer, const Mat4 &transform, std::vector<Vec2> &linePoints, Color4F color);

	struct LinePoint {
		Vec2 pos;
		float velocity;
		LinePoint(Vec2 p, float v) : pos(p), velocity(v) {}
		
	};
	std::vector<LinePoint> _lstLinePoint;

	int _cuscount = 0;
	std::vector<LinePoint> _lstLineDraw;
	std::vector<Vec2> _lstDraw;
	std::vector<Vec2> _lstDelta;
	Vec2 _cusPos;
	cocos2d::CustomCommand  _renderCommand;
	cocos2d::DrawNode *_drawNode;
	int _fsign = 1;

    
	
};