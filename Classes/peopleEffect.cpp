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
	rest_Time = 60;
	del_Time = 60;
	scheduleUpdate();
	this->setCascadeOpacityEnabled(true);
	
	return true;
}

void peopleEffect::onEnter()
{
	auto size = (this->getBoundingBox()).size;
	log("%lf %lf", size.width, size.height);
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	PhysicsBody *body = PhysicsBody::createBox(Size(size.width,size.height),material);
	body->setDynamic(false);
	body->setCategoryBitmask(0);
	this->setPhysicsBody(body);
	scheduleUpdate();
}
void peopleEffect::update(float dt)
{
	rest_Time--;
	log("rest_Time : %d", rest_Time);
	if(rest_Time <= 0) removeFromParentAndCleanup(true);
	this->setOpacity(GLubyte(255 * sqrt(rest_Time * 1.0 / del_Time))); 
}