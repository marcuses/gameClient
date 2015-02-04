#include "Monster.h"
#include "Headfile.h"
bool Monster::init()
{
	_type = rand() % 2;
	char txt[100];
	sprintf_s(txt, "boy%d_1_1.png", _type + 1);
	if (!Sprite::initWithFile(txt)) {
		return false;
	}
	_speed = 200;
	_dir = 1;
	auto size = this->getContentSize();
	//_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	//_progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
//	this->addChild(_progress);
	this->setTag(TYPE::MONSTER);
	addPhysics();
	addRunAnimation();
	return true;
}

void Monster::addPhysics()
{
	auto size = this->getContentSize();
	PhysicsBody *body = PhysicsBody::create();
	auto mater = PhysicsMaterial(100.0f, 0.0f, 0.4f);
	body->addShape(PhysicsShapeBox::create(size,mater));
	body->setCategoryBitmask(TYPE::MONSTER);
	body->setCollisionBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::BRICK);
	body->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::BRICK);
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setRotationEnable(false);
	body->setGravityEnable(true);
	this->setPhysicsBody(body);
}

void Monster::addRunAnimation()
{
	Vector<SpriteFrame*> allFrames;
	char txt[100];
	for(int i = 1;i <= 5; i++)
	{
		sprintf_s(txt, "boy%d_1_%d.png",_type + 1, i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 43, 63));
		allFrames.pushBack(sf);
	}
	auto runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
	runAction(RepeatForever::create(Animate::create(runAni)));
}

void Monster::update(float dt)
{
	auto p = getPosition();
	setPosition(p.x + dt * _dir * _speed, p.y);
	setScaleX(_dir == 1 ? 1 : -1);
}

void Monster::changeDir()
{
	_dir = -_dir;
}