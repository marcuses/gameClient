#include"dynamicTrap.h"
#include "Headfile.h"
bool dynamicTrap::init()
{
	if (!Sprite::initWithFile("ci.png")) {
		return false;
	}
	this->setTag(TYPE::TRAP);
	auto size = (this->getBoundingBox()).size;
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	PhysicsBody *body = PhysicsBody::createBox(Size(size.width,size.height),material);
	//	body->addShape(PhysicsShapeBox::create(Size(size.width,size.height),material));
	body->setCategoryBitmask(TYPE::TRAP);
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(TYPE::TRAP | TYPE::HERO);
	body->setDynamic(true);
	body->setGravityEnable(true);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	scheduleUpdate();
	return true;
}

void dynamicTrap::update(float dt)
{
	if(this->getPositionY() < -10)
	{
		removeFromParentAndCleanup(true);
	}
}