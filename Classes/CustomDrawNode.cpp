//
//  CustomDrawNode.cpp
//  TestCC01
//
//  Created by Nguyen Tan Loc on 6/13/16.
//
//

#include "CustomDrawNode.h"

USING_NS_CC;

bool CustomDrawNode::init()
{
	if (!Node::init())
		return false;

	setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));

	spr = Sprite::create("HelloWorld.png");
	spr->retain();

	listVertex = new Vec2[(SEGMENT + 1) * 2];
	listTexCoord = new Vec2[(SEGMENT + 1) * 2];

	this->scheduleUpdate();
	numDraw = SEGMENT * 2;
	//this->schedule(schedule_selector(CustomDrawNode::updateDraw), 1.0f, SEGMENT * 2, 0);
	return true;
}

void CustomDrawNode::updateDraw(float dt)
{
	numDraw += 1;
	glDrawArrays(GL_TRIANGLE_STRIP, 0, numDraw);
}

void CustomDrawNode::onDraw()
{
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins();

	// bind texture
	GL::bindTexture2D(spr->getTexture()->getName());
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);

	// send data
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, listVertex);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, listTexCoord);

	// draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, numDraw); 
}

void CustomDrawNode::update(float dt)
{
	//angle += 45 * dt;
	angle = 45 * dt;
	float w = 400;
	float h = 200;
	for (int i = 0; i <= SEGMENT; i++)
	{
		listVertex[i * 2].x = w * ((float)i / SEGMENT) + getPositionX();
		listVertex[i * 2 + 1].x = w * ((float)i / SEGMENT) + getPositionX();

		float A = cosf(CC_DEGREES_TO_RADIANS(angle) + (M_PI * i) / 10);
		//float A = 0;
		listVertex[i * 2].y = getPositionY() + A * 10;
		listVertex[i * 2 + 1].y = h + getPositionY() + A * 10;

		listTexCoord[i * 2].x = (float)i / SEGMENT;
		listTexCoord[i * 2 + 1].x = (float)i / SEGMENT;

		listTexCoord[i * 2].y = 1;
		listTexCoord[i * 2 + 1].y = 0;
	}
}

void CustomDrawNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_renderCommand.init(1);
	_renderCommand.func = CC_CALLBACK_0(CustomDrawNode::onDraw, this);
	renderer->addCommand(&_renderCommand);
}