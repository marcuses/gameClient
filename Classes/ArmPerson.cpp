#include "ArmPerson.h"

bool ArmPerson::init() //note : this init should used after son create
{
	//Sprite::create();
	_dir = 1;
	_speed = 180.0f;
	addRunAnimation();
	addPhysics();
	return true;
}

void ArmPerson::changeDir()
{
	_dir = -_dir;
}

void ArmPerson::addPhysics()
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
	else
	{
		body->setCollisionBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::TRAP);
		body->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::TRAP);
	}
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setRotationEnable(false);
	body->setGravityEnable(true);
	this->setPhysicsBody(body);
}

void ArmPerson::addRunAnimation()
{
	//¼Ó¶¯»­
}

void ArmPerson::setSpeed(float speed)
{
	_speed = speed;
}
float ArmPerson::getSpeed()
{
	return _speed;
}
void ArmPerson::setType(TYPE type) 
{
	_type = type;
}
TYPE ArmPerson::getType()
{
	return _type;
}
int ArmPerson::getDir()
{
	return _dir;
}
void ArmPerson::setDir(int dir)
{
	_dir = dir;
}