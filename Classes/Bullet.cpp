#include "Bullet.h"
#include"cocostudio/CocoStudio.h"
using namespace cocostudio;
Bullet* Bullet::create(TYPE type,Vec2 dir, float speed, int bType, bool track){

	Bullet* ret = new Bullet();  


	if(ret&&ret->init(type, dir, speed, bType, track)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//安全删除  
	return nullptr;  
}  

bool Bullet::init(TYPE type,Vec2 dir, float speed, int bType, bool track) //note : this init should used after son create
{
	char txt[100];
	sprintf(txt,"bullet%d.png", bType);
	if (!Sprite::initWithFile(txt))	return false;
	_type = type;
	_track = track;
	_bType = bType;
	_dir = dir;
	_speed = speed;
	setScale(0.7);
	addAction();
	addPhysics();
	this->setTag(type);
	this->getPhysicsBody()->setVelocity(_dir * _speed);
	float anc = atan2(_dir.y, _dir.x);
	this->setRotation(- anc * 180.0 / 3.1415);
	_maxTime = 1;
	if(type == BULLET) _maxTime = 1.2;
	else{
		if(bType == 5)
			_maxTime = 3;
		else
			_maxTime = 5;
	}
	_nowTime = _maxTime;
	this->setCascadeOpacityEnabled(true);
	scheduleUpdate();
	return true;
}

void Bullet::addPhysics()
{
	auto body = PhysicsBody::create();
	body->addShape(PhysicsShapeBox::create(this->getContentSize() * 0.7,PhysicsMaterial(0.0f, 0.01f, 1.0f)));
	
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
//	armature->setScale(0.5);
	this->addChild(armature);
	armature->getAnimation()->play("run");
}
void Bullet::del()
{
	removeFromParentAndCleanup(true);
}
void Bullet::update(float dt)
{
	_nowTime -= dt;
	if(_nowTime<=0){
		del();
	}else{
		if(_track)
		{
			Point pos1 = this->getParent()->getChildByTag(TYPE::HERO)->getPosition();
			Point pos2 = this->getPosition();
			Vec2 dire = pos1 - pos2;
			dire.normalize();
			_dir = dire;
		}
		getPhysicsBody()->setVelocity(_dir * _speed);
		float anc = atan2(_dir.y, _dir.x);
		this->setRotation(- anc * 180.0 / 3.1415);
		this->setOpacity(GLubyte(255*sqrt(_nowTime/_maxTime)));  //设置透明度
	}
}