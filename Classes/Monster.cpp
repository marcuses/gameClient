#include "Monster.h"
#include "Headfile.h"
#include "Bullet.h"
Monster* Monster::create(int mType){

	Monster* ret = new Monster();  


	if(ret&&ret->init(mType)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  
bool Monster::init(int mType)
{
	_monsterType = mType + 1;
	char txt[100];
	sprintf_s(txt, "Monster%d.png", _monsterType );
	if (!Sprite::initWithFile(txt)) {
		return false;
	}

	setScale(0.7);
	schedule(schedule_selector(Monster::updateBullet),4);
	scheduleUpdate();
	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	Person::init(_monsterType );
	return true;
}
void Monster::onEnter()
{
	Person::onEnter();
	//addRunAnimation();
	auto size = getContentSize();
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	_progress->setScaleY(0.6);
	_progress->setScaleX(0.8);
	_progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
	addChild(_progress);
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
//	_armAnimation->stop();
	_armAnimation->play("attack");
	_state = STATE::attack;	
}
void Monster::addRunAnimation()
{
	char txt[100];
	sprintf(txt, "Monster%d", _monsterType);
	_armature = Armature::create(txt);
//	_armature->setScale(monster_data[_monsterType].armScale);
	_armature->setAnchorPoint(Point(0,0));
	this->addChild(_armature);
	_armature->getAnimation()->setFrameEventCallFunc( this , frameEvent_selector (Monster ::onFrameEvent)); 
	_armAnimation = _armature->getAnimation();
	_armAnimation->play("run");;
	_state = STATE::run;
}

void Monster::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	if(evt == "attack")
	{
		//write attack AI here
		CCPoint p = getPosition();
		auto bullet = Bullet::create(BULLETENEMY, Vec2(getDir(), 0), 250, _monsterType);
		bullet->setPosition(p);
		getParent()->addChild(bullet, 2);
		_armAnimation->play("run");
	}
	
}
void Monster::beHit()
{
	Person::beHit();
	if(_curLife < 0) return;
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	_progress->setProgress(_curLife * 1.0 / _maxLife * 100);
	_spHit->setVisible(true);
	_spHitTime = 0;
	if(_isDead)
	{
		_armAnimation->play("dead");
		getPhysicsBody()->setCategoryBitmask(0);
		getPhysicsBody()->setCollisionBitmask(0);
		getPhysicsBody()->setContactTestBitmask(0);
		Vec2 v = getPhysicsBody()->getVelocity();
		getPhysicsBody()->setVelocity(Vec2(v.x, 50));
		scheduleOnce(schedule_selector(Monster::removeThis), 1);	
	}
}

void Monster::removeThis(float dt)
{
	getParent()->removeChild(this, true);
}
void Monster::update(float dt)
{
	if(_isDead) return;
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	setScaleX(getDir() == 1 ? -1 : 1);
	_spHit->setPosition(Vec2(30, 30) );
	if(_spHit->isVisible())
	{
		_spHitTime++;
		if(_spHitTime >= 10) _spHit->setVisible(false);
	}
}
