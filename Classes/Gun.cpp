#include "Gun.h"
#include "Headfile.h"
#include "Bullet.h" 
Gun* Gun::create(int mhard){
	Gun* ret = new Gun();  
	if(ret&&ret->init(mhard)){  
		ret->autorelease();  
		return ret;  
	}  
	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
} 
bool Gun::init(int mhard)
{
	_hard = mhard;
	if (!Sprite::initWithFile("pao.png")) {
		return false;
	}
//	setScale(0.7);
	float f = 5 - _hard;
	schedule(schedule_selector(Gun::updateBullet),f);
	scheduleUpdate();
	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	Person::init(3 + _hard);
	return true;
}
void Gun::onEnter()
{
	Person::onEnter();
	//addRunAnimation();
	auto size = getContentSize();
	getPhysicsBody()->setDynamic(false);
	//	if(_monsterType >= 2) this->setScale(0.25);
	_spHit = Sprite::create("boom.png");
	addChild(_spHit, 1);
	_spHit->setVisible(false);
	_spHitTime = 0;
	_isDead = false;
	_spHit->setScale(0.5);
}
void Gun::updateBullet(float dt)
{
	if(_isDead||outScene()) return;
	//	_armAnimation->stop();
	
	auto bullet3 = Bullet::create(BULLETENEMY, Vec2(getDir(),-getDir()), 150, 5, true);
	bullet3->setPosition(this->getPosition());
	getParent()->addChild(bullet3, 2);
}
bool Gun::outScene(){
	float tmp = getPositionX()+getParent()->getPositionX();
	return tmp<0||tmp>Director::getInstance()->getVisibleSize().width;
}
void Gun::addRunAnimation()
{

}
void Gun::beHit(Vec2 dir)
{
	Person::beHit(Vec2(0,0));
	if(_curLife < 0) return;
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	_spHit->setVisible(true);
	_spHitTime = 0;
	if(_isDead)
	{
		getPhysicsBody()->setCategoryBitmask(0);
		getPhysicsBody()->setCollisionBitmask(0);
		getPhysicsBody()->setContactTestBitmask(0);
		SimpleAudioEngine::getInstance()->playEffect("explode.wav");
		Vec2 v = getPhysicsBody()->getVelocity();
		scheduleOnce(schedule_selector(Gun::removeThis), 1);	
	}
}
void Gun::removeThis(float dt)
{
	getParent()->removeChild(this, true);
}
void Gun::update(float dt)
{
	if(_isDead) return;
	_spHit->setPosition(Vec2(30, 30) );
	if(_spHit->isVisible())
	{
		_spHitTime++;
		if(_spHitTime >= 10) _spHit->setVisible(false);
	}
}
