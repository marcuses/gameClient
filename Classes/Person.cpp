#include "Person.h"

bool Person::init() //note : this init should used after son create
{
	//Sprite::create();
	_dir = 1;
	_speed = 180.0f;
	addRunAnimation();
	addPhysics();
	return true;
}

void Person::changeDir()
{
	_dir = -_dir;
}

void Person::addPhysics()
{
	auto size = this->getContentSize();
	PhysicsBody *body = PhysicsBody::create();
	auto material = PhysicsMaterial(100.0f, 0.01f, 1.0f);
	body->addShape(PhysicsShapeBox::create(Size(size.width/2,size.height),material));
	body->setCategoryBitmask(_type);
	if(_type == TYPE::MONSTER) 
	{
		body->setCollisionBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::BRICK | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET );
		body->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::BRICK | TYPE::TANGH | TYPE::BULLET );
	}
	else if(_type == TYPE::HERO)
	{
		body->setCollisionBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::TRAP | TYPE::BOSS | TYPE::BULLETENEMY);
		body->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::TRAP | TYPE::BOSS | TYPE::BULLETENEMY);
	}
	else if(_type == TYPE::BOSS)
	{
		body->setCollisionBitmask( TYPE::HERO | TYPE::GROUND | TYPE::BOSS );
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