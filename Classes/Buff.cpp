#include"Buff.h"
#include "Headfile.h"
Buff* Buff::create(int type){

	Buff* ret = new Buff();  


	if(ret&&ret->init(type)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  
bool Buff::init(int type)
{
	char txt[100];
	_type = type;
	sprintf(txt, "buff%d.png", type);
	if (!Sprite::initWithFile(txt)) {
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
