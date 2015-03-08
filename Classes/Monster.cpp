#include "Monster.h"
#include "Headfile.h"
bool Monster::init()
{
	_monsterType = rand() % 3;
	char txt[100];
	sprintf_s(txt, "boy%d_1_1.png", _monsterType + 1);
	if (!Sprite::initWithFile(txt)) {
		return false;
	}
	this->removeAllChildren();
	addRunAnimation();
//	if(_monsterType >= 2) this->setScale(0.25);
	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	Person::init();
	return true;
}

void Monster::addRunAnimation()
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

		armature->setScale(100 / 671.0);
		armature->setAnchorPoint(Point(0,0));
	//	armature->setPosition(Point(5700, 320));
		
		this->addChild(armature);
		//²¥·Å¶¯»­
		armature->getAnimation()->play("walk");
	}
}

void Monster::update(float dt)
{
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	if(_monsterType < 2)setScaleX(getDir() == 1 ? 1 : -1);
	else setScaleX(getDir() == 1 ? -1 : 1);
}
