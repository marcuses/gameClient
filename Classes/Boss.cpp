#include "Boss.h"
#include "Headfile.h"
#include "MainScene.h"
bool Boss::init()
{
	_monsterType = 2;
	if (!Sprite::initWithFile("boss1.png")) {
		return false;
	}
	addRunAnimation();
	//	if(_monsterType >= 2) this->setScale(0.25);
	this->setTag(TYPE::BOSS);
	setType(TYPE::BOSS);
	Person::init();
	setSpeed(0);
	setDir(-1);
	_time = 0;
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Boss::shoot), strEnemyShoot, NULL);
	scheduleUpdate();
	return true;
}

void Boss::addRunAnimation()
{
	if(_monsterType < 2)
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
	else
	{
		ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation0.png","NewAnimation0.plist","NewAnimation.ExportJson");

		Armature *armature = Armature::create("NewAnimation");

	//	armature->setScale(600 / 671.0);
		armature->setAnchorPoint(Point(0,0));
		//	armature->setPosition(Point(5700, 320));

		this->addChild(armature);
		//²¥·Å¶¯»­
		armature->getAnimation()->play("walk");
	}
}

void Boss::shoot(Object * object)
{
	Point pos1 = ((MainScene*)this->getParent())->getPlayerPosition();
	Point pos2 = this->getPosition();
	Vec2 dire = pos1 - pos2;
	dire.normalize();
	auto bullet = Bullet::create(BULLETENEMY, dire, 180);
	bullet->setPosition(pos2);
	this->getParent()->addChild(bullet, 2);
}
void Boss::update(float dt)
{
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	if(_monsterType < 2)setScaleX(getDir() == 1 ? 1 : -1);
	else setScaleX(getDir() == 1 ? -1 : 1);
	_time = (_time + 1) % 180;
	if(_time == 0) 
		NotificationCenter::getInstance()->postNotification(strEnemyShoot);
}
