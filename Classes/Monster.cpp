#include "Monster.h"
#include "Headfile.h"
#include "Bullet.h"
bool Monster::init()
{
	_monsterType = 2;
	char txt[100];
	//sprintf_s(txt, "boy%d_1_1.png", _monsterType + 1);
	if (!Sprite::initWithFile("Monster1.png")) {
		return false;
	}
//	addRunAnimation();
	schedule(schedule_selector(Monster::updateBullet),4);
	scheduleUpdate();
	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	Person::init(_monsterType + 1);
	return true;
}
void Monster::onEnter()
{
	Person::onEnter();
	addRunAnimation();
	auto size = this->getContentSize();
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	_progress->setScaleY(0.6);
	_progress->setScaleX(0.8);
	_progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
	this->addChild(_progress);
	//	if(_monsterType >= 2) this->setScale(0.25);
	
	_spHit = Sprite::create("hitBlode.png");
	addChild(_spHit, 1);
	_spHit->setVisible(false);
	_spHitTime = 0;
	_isDead = false;
	_spHit->setScale(0.5);
	
}
void Monster::updateBullet(float dt)
{
	if(_isDead) return;
	_armAnimation->play("attack");
	_state = STATE::attack;
	auto bullet = Bullet::create(BULLETENEMY, Vec2(getDir(), 0), 250);
	bullet->setPosition(this->getPosition());
	getParent()->addChild(bullet, 2);
	scheduleOnce(schedule_selector(Monster::atkToRun),0.5);	
}
void Monster::addRunAnimation()
{
	/*if(_monsterType < 2)
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
		*/

		_armature = Armature::create("Monster1");
		_armature->setScale(0.7);
		_armature->setAnchorPoint(Point(0,0));
		this->addChild(_armature);
		_armAnimation = _armature->getAnimation();
		//²¥·Å¶¯»­
		_armAnimation->play("attack");
		_state = STATE::run;
	//}
}

void Monster::beHit()
{
	Person::beHit();
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	_progress->setProgress(_curLife * 1.0 / _maxLife * 100);
	_spHit->setVisible(true);
	_spHitTime = 0;
	if(_isDead)
	{
		_armAnimation->play("dead");
		scheduleOnce(schedule_selector(Monster::removeThis),1);	
	}
}

void Monster::removeThis(float dt)
{
	getParent()->removeChild(this, true);
}

void Monster::atkToRun(float dt)
{
	_state = run;
	_armAnimation->play("run");
} 
void Monster::update(float dt)
{
	if(_isDead) return;
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	if(_monsterType < 2)setScaleX(getDir() == 1 ? 1 : -1);
	else setScaleX(getDir() == 1 ? -1 : 1);
	_spHit->setPosition(Vec2(30, 30) );
	if(_spHit->isVisible())
	{
		_spHitTime++;
		if(_spHitTime >= 10) _spHit->setVisible(false);
	}


}
