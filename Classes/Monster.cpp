#include "Monster.h"
#include "Headfile.h"
bool Monster::init()
{
	_monsterType = rand() % 2;
	char txt[100];
	sprintf_s(txt, "boy%d_1_1.png", _monsterType + 1);
	if (!Sprite::initWithFile(txt)) {
		return false;
	}

	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	Person::init();
	return true;
}

void Monster::addRunAnimation()
{
	Vector<SpriteFrame*> allFrames;
	char txt[100];
	for(int i = 1;i <= 5; i++)
	{
		sprintf_s(txt, "boy%d_1_%d.png",_monsterType + 1, i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 43, 63));
		allFrames.pushBack(sf);
	}
	auto runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
	runAction(RepeatForever::create(Animate::create(runAni)));
}

void Monster::update(float dt)
{
//	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	setScaleX(getDir() == 1 ? 1 : -1);
}
