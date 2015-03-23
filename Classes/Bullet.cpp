#include "Bullet.h"
#include"cocostudio/CocoStudio.h"
using namespace cocostudio;
Bullet* Bullet::create(TYPE type,Vec2 dir, float speed, int bType){

	Bullet* ret = new Bullet();  


	if(ret&&ret->init(type, dir, speed, bType)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  

bool Bullet::init(TYPE type,Vec2 dir, float speed, int bType) //note : this init should used after son create
{
	char txt[100];
	sprintf(txt,"bullet%d.png", bType);
	if (!Sprite::initWithFile(txt))	return false;
	_type = type;
	_bType = bType;
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
	body->addShape(PhysicsShapeBox::create(this->getContentSize() ,PhysicsMaterial(0.0f, 0.01f, 1.0f)));
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
	char txt[100];
	sprintf(txt, "bullet%d", _bType);
	auto armature = Armature::create(txt);
	armature->setAnchorPoint(Point(0,0));
	this->addChild(armature);
	armature->getAnimation()->play("run");
}
void Bullet::del(float dt)
{
	removeFromParentAndCleanup(this);
}
void Bullet::update(float dt)
{
	getPhysicsBody()->setVelocity(_dir * _speed);
	float anc = atan2(_dir.y, _dir.x);
	this->setRotation(- anc * 180.0 / 3.1415);
}