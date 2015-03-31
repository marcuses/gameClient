#include "Person.h"

Person* Person::create(int maxLife)
{
	Person* ret = new Person();
	if(ret && ret->init(maxLife))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}
bool Person::init(int maxLife) //note : this init should used after son create
{
	//Sprite::create();
	_dir = 1;
	_speed = 180.0f;
	_atkTime = 0;
	_isDead = false;
	_curLife = maxLife;
	_maxLife = maxLife;
	return true;
}
void Person::onEnter()
{
	Sprite::onEnter();
	addRunAnimation();
	addPhysics();
}
int Person::getLife(){
	return _curLife;
}
void Person::beHit(Vec2 dir)
{
	if(_isDead) return;
	getPhysicsBody()->setVelocity(dir * 0.5);
	_curLife--;
	if(_curLife <= 0)
	{
		_curLife = 0;
		_isDead = true;
	}
}
void Person::changeDir()
{
	_dir = -_dir;
}

void Person::addPhysics()
{
	auto size = (this->getBoundingBox()).size;
	log("%lf %lf", size.width, size.height);
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	if(_type == TYPE::HERO) size.width /= 2;
	PhysicsBody *body = PhysicsBody::createBox(Size(size.width,size.height),material);
//	body->addShape(PhysicsShapeBox::create(Size(size.width,size.height),material));
	body->setCategoryBitmask(_type);
	if(_type == TYPE::MONSTER) 
	{
		body->setCollisionBitmask(TYPE::MONSTER  | TYPE::BRICK | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::BOSS | TYPE::PLANK);
		body->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::BRICK | TYPE::TANGH | TYPE::BULLET | TYPE::BOSS);
	}
	else if(_type == TYPE::HERO)
	{
		body->setCollisionBitmask( TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::PLANK);
		body->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::TRAP | TYPE::BOSS | TYPE::BULLETENEMY | TYPE::PLANK | TYPE::BUFF);
	}
	else if(_type == TYPE::BOSS)
	{
		body->setCollisionBitmask( TYPE::HERO | TYPE::GROUND | TYPE::BOSS | PLANK);
		body->setContactTestBitmask( TYPE::HERO | TYPE::GROUND | TYPE::BOSS);
	}
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setRotationEnable(false);
	body->setGravityEnable(true);
	this->setPhysicsBody(body);
}

void Person::addRunAnimation()
{
	//¼Ó¶¯»­
}

void Person::setSpeed(float speed)
{
	_speed = speed;
}
float Person::getSpeed()
{
	return _speed;
}
void Person::setType(TYPE type) 
{
	_type = type;
}
TYPE Person::getType()
{
	return _type;
}
int Person::getDir()
{
	return _dir;
}
void Person::setDir(int dir)
{
	_dir = dir;
}