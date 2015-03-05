#include "Bullet.h"

bool Bullet::init() //note : this init should used after son create
{
	if (!Sprite::initWithFile("skill_fore.png"))	return false;
	addPhysics();
	this->setTag(TYPE::BULLET);
	return true;
}

void Bullet::addPhysics()
{
	auto body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(this->getContentSize().width / 2,PhysicsMaterial(100.0f, 0.01f, 1.0f)));
	body->setCategoryBitmask(TYPE::BULLET);
	body->setCollisionBitmask(TYPE::BULLET | TYPE::MONSTER | TYPE::HERO);
	body->setContactTestBitmask(TYPE::BULLET | TYPE::MONSTER | TYPE::HERO);
	body->setLinearDamping(0.0f);
	body->setDynamic(true);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);
}

void Bullet::update(float dt)
{
	this->getPhysicsBody()->setVelocity(_dir * _speed);
	//setPosition(getPosition() + _dir * _speed);
	//Point o = getPosition();
}