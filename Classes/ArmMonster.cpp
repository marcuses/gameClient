#include "ArmMonster.h"
#include "Headfile.h"
bool ArmMonster::init()
{
	/*_monsterType = 2;
	char txt[100];
	sprintf_s(txt, "boy%d_1_1.png", _monsterType + 1);
	if (!Sprite::initWithFile(txt)) {
		return false;
	}
	this->removeAllChildren();*/
	_monsterType = 2;
	ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation0.png","NewAnimation0.plist","NewAnimation.ExportJson");

	if(!Armature::create("NewAnimation")) return false;
	this->setScale(100 / 671.0);
	addRunAnimation();
	//	if(_monsterType >= 2) this->setScale(0.25);
	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	ArmPerson::init();
	return true;
}

void ArmMonster::addRunAnimation()
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
		//²¥·Å¶¯»­
		this->getAnimation()->play("walk");
	}
}

void ArmMonster::update(float dt)
{
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	setScaleX(getDir() == 1 ? 1 : -1);
}
