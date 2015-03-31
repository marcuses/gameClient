#include"dynamicTrap.h"
#include "Headfile.h"

dynamicTrap* dynamicTrap::create(const char* imgname){

	dynamicTrap* ret = new dynamicTrap();  


	if(ret&&ret->init(imgname)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  
bool dynamicTrap::init(const char *imgname)
{
	if (!Sprite::initWithFile(imgname)) {
		return false;
	}
	this->setTag(TYPE::TRAP);
	_isFire = false;
	auto size = (this->getBoundingBox()).size;
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	PhysicsBody *body = PhysicsBody::createBox(Size(size.width,size.height),material);
	//	body->addShape(PhysicsShapeBox::create(Size(size.width,size.height),material));
	body->setCategoryBitmask(TYPE::TRAP);
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(TYPE::TRAP | TYPE::HERO);
	body->setDynamic(true);
	if(imgname == "fireTrap.png"){
		body->setDynamic(false);
		_isFire = true;
	}
	body->setGravityEnable(true);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	scheduleUpdate();
	return true;
}

void dynamicTrap::update(float dt)
{
	if(_isFire && !getPhysicsBody()->isDynamic())
	{
		float x1 = this->getPositionX();
		float x2 = this->getParent()->getChildByTag(TYPE::HERO)->getPositionX();
		if(this != NULL && 
			fabs(x1 - x2) <= 30)
		{
			this->getPhysicsBody()->setDynamic(true);
			this->getPhysicsBody()->setVelocity(Vec2(0, -100));
		}
	}
	if(this->getPositionY() < -10)
	{
		removeFromParentAndCleanup(true);
	}
	
	
//	if()
}