#include"Buff.h"
#include "Headfile.h"
bool Buff::init()
{
	if (!Sprite::initWithFile("buff.png")) {
		return false;
	}
	this->setTag(TYPE::BUFF);
	auto size = (this->getBoundingBox()).size;
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	PhysicsBody *body = PhysicsBody::createBox(Size(size.width,size.height),material);
	//	body->addShape(PhysicsShapeBox::create(Size(size.width,size.height),material));
	body->setCategoryBitmask(TYPE::BUFF);
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(TYPE::BUFF | TYPE::HERO);
	body->setDynamic(false);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	return true;
}
