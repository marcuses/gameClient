#include "peopleEffect.h"
#include "string.h"

peopleEffect* peopleEffect::create()
{
	peopleEffect* ret = new peopleEffect();
	if(ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}
bool peopleEffect::init()
{
	if (!Sprite::initWithFile("player_1_4.png"))	return false;
	
	setTag(TYPE::NOTHING);
	del_Time  = 0.5;
	rest_Time = del_Time;
	this->setCascadeOpacityEnabled(true);
	scheduleUpdate();

	return true;
}

void peopleEffect::onEnter()
{
	Sprite::onEnter();
	auto size = (this->getBoundingBox()).size;
	log("%lf %lf", size.width, size.height);
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	PhysicsBody *body = PhysicsBody::createBox(Size(size.width,size.height),material);
	body->setDynamic(false);
	body->setCategoryBitmask(0);
	this->setPhysicsBody(body);
}
void peopleEffect::update(float dt)
{
	rest_Time -= dt;
	log("rest_Time : %d", rest_Time);
	if(rest_Time <= 0)	removeFromParentAndCleanup(true);
	else				this->setOpacity(GLubyte(255 * sqrt(rest_Time / del_Time))); 
}