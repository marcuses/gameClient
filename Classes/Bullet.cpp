#include "Bullet.h"

Bullet* Bullet::create(TYPE type){

	Bullet* ret = new Bullet();  


	if(ret&&ret->init(type)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//��ȫɾ��  
	return nullptr;  
}  

bool Bullet::init(TYPE type) //note : this init should used after son create
{
	if (!Sprite::initWithFile("bu1.png"))	return false;
	_type = type;
	addAction();
	addPhysics();
	_time = 0;
	this->setTag(type);
	return true;
}

void Bullet::addPhysics()
{
	auto body = PhysicsBody::create();
	body->addShape(PhysicsShapeBox::create(this->getContentSize() ,PhysicsMaterial(100.0f, 0.01f, 1.0f)));
	body->setCategoryBitmask(_type);
	body->setCollisionBitmask(_type | TYPE::MONSTER | TYPE::HERO);
	body->setContactTestBitmask(_type | TYPE::MONSTER | TYPE::HERO);
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
void Bullet::update(float dt)
{
	this->getPhysicsBody()->setVelocity(_dir * _speed);
	float anc = atan2(_dir.y, _dir.x);
	log("%lf",anc);
	this->setRotation(- anc * 180.0 / 3.1415);
	_time++;
	//setPosition(getPosition() + _dir * _speed);
	//Point o = getPosition();
}