#include "Bullet.h"

Bullet* Bullet::create(TYPE type,Vec2 dir, float speed){

	Bullet* ret = new Bullet();  


	if(ret&&ret->init(type, dir, speed)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  

bool Bullet::init(TYPE type,Vec2 dir, float speed) //note : this init should used after son create
{
	if (!Sprite::initWithFile("bu1.png"))	return false;
	_type = type;
	_dir = dir;
	_speed = speed;
	addAction();
	addPhysics();
	this->setTag(type);
	this->getPhysicsBody()->setVelocity(_dir * _speed);
	float anc = atan2(_dir.y, _dir.x);
	this->setRotation(- anc * 180.0 / 3.1415);
	float delTime = 1;
	if(type == BULLET) delTime = 1.2;
	else delTime = 5;
 	scheduleOnce(schedule_selector(Bullet::del), delTime);
	scheduleUpdate();
	return true;
}

void Bullet::addPhysics()
{
	auto body = PhysicsBody::create();
	body->addShape(PhysicsShapeBox::create(this->getContentSize() ,PhysicsMaterial(100.0f, 0.01f, 1.0f)));
	body->setCategoryBitmask(_type);
	body->setCollisionBitmask(_type | TYPE::MONSTER | TYPE::HERO | BOSSWEAKNESS);
	body->setContactTestBitmask(_type | TYPE::MONSTER | TYPE::HERO | BOSSWEAKNESS);
	body->setLinearDamping(0.0f);
	body->setDynamic(true);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);
}

void Bullet::addAction()
{
	Vector<SpriteFrame*> allFrames;
	char txt[100];
	for(int i = 1;i <= 6; i++)
	{
		sprintf_s(txt, "bu%d.png", i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 82, 39));
		allFrames.pushBack(sf);
	}
	auto runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
	runAction(RepeatForever::create(Animate::create(runAni)));
}
void Bullet::del(float dt)
{
	removeFromParentAndCleanup(this);
}
void Bullet::update(float dt)
{
	this->getPhysicsBody()->setVelocity(_dir * _speed);
	float anc = atan2(_dir.y, _dir.x);
	this->setRotation(- anc * 180.0 / 3.1415);
}