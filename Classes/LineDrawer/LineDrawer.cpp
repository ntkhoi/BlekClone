
#include "LineDrawer.h"
#include <chrono>
//#include "Tutorial/TutorialScene.h"
//#include "TutorialScene.h"
USING_NS_CC;

LineDrawer::~LineDrawer()
{
    
}

bool LineDrawer::init()
{
    
    
    isResetDrawLine = false;
    _drawNode = DrawNode::create();
    this->addChild(_drawNode);
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = [this](Touch *touch, Event *event) -> bool {
        
        _isColissionBlackSpr = false;
        _isColissionBlueSpr = false;
        isResetDrawLine = true;
        this->unscheduleUpdate();
        _lstDraw.clear();
        _drawNode->clear();
        _lstDelta.clear();
        _lstDraw.push_back(touch->getLocation());
        _cusPos = touch->getLocation();
        _fsign = 1;
        
        return true;
    };
    
    eventListener->onTouchMoved = [this](Touch *touch, Event *event) {
        
        
        
        
        
        auto delta = touch->getLocation() - touch->getPreviousLocation();
        
        
        if(!_isColissionBlackSpr && !_isColissionBlueSpr)
        {
            
            if(delta.getLength() > 1 )
            {
                _lstDelta.push_back(delta);
                _cusPos = touch->getLocation();
                _lstDraw.push_back(touch->getLocation());
                
            }
        }
        
        else
        {
            return ;
        }
        
        
        
    };
    
    eventListener->onTouchEnded = [&](Touch *touch, Event *event) {
        
        this->scheduleUpdate();
        _cuscount = 0;
        
        Vec2 delta = touch->getLocation() - touch->getPreviousLocation();
        
        ;
        
        
        if(!_isColissionBlackSpr && !_isColissionBlueSpr)
        {
            _cusPos = touch->getLocation();
            _lstDraw.push_back(touch->getLocation());
            _lstDelta.push_back(delta);
            
        }
        else{
            return;}
        
        
        
        
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(eventListener, 1);
    
    return true;
    
}

void LineDrawer::update(float dt)
{
    
    if(_isColissionBlackSpr)
    {
        if(!_lstDraw.empty())
        {
            _lstDraw.erase(_lstDraw.begin());
        }
        
        return;
        
    }
    if(!_lstDraw.empty())
    {
        if (_cuscount < _lstDelta.size() - 1)
        {
            _lstDraw.erase(_lstDraw.begin());
            Vec2 cusdelta = _lstDelta[_cuscount];
            cusdelta.x = _fsign *cusdelta.x;
            _cusPos += cusdelta;
            
            if (_cusPos.x <= 0 || _cusPos.x >= Director::getInstance()->getVisibleSize().width)
            {
                _fsign = _fsign*(-1);
            }
            _lstDraw.push_back(_cusPos);
            _cuscount += 1;
            
        }
        else
        {
            /*_lstDraw.clear();
             _drawNode->clear();*/
            _cuscount = 0;
        }
    }
    
}


void LineDrawer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _renderCommand.init(1);
    _renderCommand.func = CC_CALLBACK_0(LineDrawer::onDraw, this);
    renderer->addCommand(&_renderCommand);
}

void LineDrawer::onDraw()
{
    //Draw line
    //    _drawNode->clear();
    //
    //    if (!_lstDraw.empty()){
    //        if (_lstDraw.size() > 2)
    //        {
    //            for (unsigned int i = 2; i <= _lstDraw.size(); ++i)
    //            {
    //                Vec2 prev2 = _lstDraw[i - 2];
    //                Vec2 prev1 = _lstDraw[i - 1];
    //
    //                _drawNode->drawLine(prev2, prev1, Color4F(1.0, 0.0, 0.0, 1.0));
    //            }
    //        }
    //    }
    
    //    Vec2 vertices[] =
    //    {
    //        Vec2(100, 80),
    //        Vec2(100, 100),
    //        Vec2(200, 80),
    //        Vec2(200, 100),
    //        Vec2(300, 100),
    //        Vec2(300, 120),
    //    };
    //
    
    if(_lstDraw.size()>2)
    {
        
        std::vector<Vec2> v ;
        
    
        
        float flineSize = 1.5;
        float nlstDrawSize = _lstDraw.size();
        
        
        for (int i = 1; i < _lstDraw.size(); i++)
        {
            
            
            
            
            if(flineSize > 0.2 )
            {
                flineSize += -1/nlstDrawSize;
            }
            Vec2 &prevPoint= _lstDraw[i -1 ];
            auto curPoint = _lstDraw[i];
            Vec2 dir = curPoint - prevPoint;
            Vec2 perp = dir.getPerp().getNormalized();
            
            Vec2 A = prevPoint + perp * flineSize;
            Vec2 B = prevPoint - perp * flineSize;
            Vec2 C = curPoint + perp * flineSize;
            Vec2 D = curPoint - perp*flineSize;
            v.push_back(A);
            v.push_back(B);
            v.push_back(C);
            v.push_back(D);
            
            //            prevPoint = _lstDraw[i-1];
            
            
        }
            
        
        
        
        auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
        
        int colorLocation = glProgram->getUniformLocation("u_color");
        
        
        
        CHECK_GL_ERROR_DEBUG();
        
        
    
        
        Color4F color(0, 0, 0, 1);
        
        glProgram->use();
        glProgram->setUniformsForBuiltins();
        glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);
        
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
        //    std::vector<Vec2> v;
        int n = (int)v.size();
        Vec2 *vecS = new Vec2[n];
        
        
        for (int i = 0; i < n; i++)
        {
            vecS[i] = v.at(i);
            
        }
        
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vecS);
        
//        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
        int numVertext =  (int)v.size();
        
        
        
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertext);
        v.clear();
        delete[] vecS;
    }
    
}


void LineDrawer::drawLineTexture(Renderer *renderer, const Mat4 &transform, std::vector<Vec2> &linePoints, Color4F color)
{
    
}


bool LineDrawer::iscollision(Sprite* sprite)
{
    bool Iscollision;
   	sprite->getPosition().getDistance(_cusPos) <= sprite->getBoundingBox().size.width / 2
    && sprite->getNumberOfRunningActions() == 0 ? Iscollision = true : Iscollision = false;
    return Iscollision;
}



