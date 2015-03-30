#include "Monster.h"
#include "Headfile.h"
#include "Bullet.h"
Monster* Monster::create(int mhard,int mType){
	Monster* ret = new Monster();  
	if(ret&&ret->init(mhard,mType)){  
		ret->autorelease();  
		return ret;  
	}  
	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  
bool Monster::init(int mhard,int mType)
{
	_monsterType = mType + 1;
	_hard = mhard;
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
	Person::init( int(_monsterType/2)+_hard );
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
	if(_isDead||outScene()) return;
//	_armAnimation->stop();
	_armAnimation->play("attack");
	_state = STATE::attack;	
}
bool Monster::outScene(){
	float tmp = getPositionX()+getParent()->getPositionX();
	return tmp<0||tmp>Director::getInstance()->getVisibleSize().width;
};
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
		switch(_hard){
		case 1: AIeasy();break;
		case 2: AImid();break;
		case 3: AIhard();break;
		default:break;
		}
		_armAnimation->play("run");
	}
	
}
void Monster::AIeasy(){
	auto bullet = Bullet::create(BULLETENEMY, Vec2(getDir(), 0), 250, _monsterType, false);
	bullet->setPosition(this->getPosition());
	getParent()->addChild(bullet, 2);
}
void Monster::AImid(){
	auto bullet1 = Bullet::create(BULLETENEMY, Vec2(getDir(), 0), 250, _monsterType, false);
	bullet1->setPosition(this->getPosition());
	getParent()->addChild(bullet1, 2);

	auto bullet2 = Bullet::create(BULLETENEMY, Vec2(-getDir(), 0), 250, _monsterType, false);
	bullet2->setPosition(this->getPosition());
	getParent()->addChild(bullet2, 2);
}
void Monster::AIhard(){
	auto bullet1 = Bullet::create(BULLETENEMY, Vec2(getDir(), 0), 250, _monsterType, false);
	bullet1->setPosition(this->getPosition());
	getParent()->addChild(bullet1, 2);

	auto bullet2 = Bullet::create(BULLETENEMY, Vec2(getDir(), getDir()), 250, _monsterType, false);
	bullet2->setPosition(this->getPosition());
	getParent()->addChild(bullet2, 2);

	auto bullet3 = Bullet::create(BULLETENEMY, Vec2(getDir(),-getDir()), 250, _monsterType, false);
	bullet3->setPosition(this->getPosition());
	getParent()->addChild(bullet3, 2);

	//auto bullet4 = Bullet::create(BULLETENEMY, Vec2(-getDir(), 0), 250, _monsterType);
	//bullet4->setPosition(this->getPosition());
	//getParent()->addChild(bullet4, 2);

	//auto bullet5 = Bullet::create(BULLETENEMY, Vec2(-getDir(), getDir()), 250, _monsterType);
	//bullet5->setPosition(this->getPosition());
	//getParent()->addChild(bullet5, 2);

	//auto bullet6 = Bullet::create(BULLETENEMY, Vec2(-getDir(),-getDir()), 250, _monsterType);
	//bullet6->setPosition(this->getPosition());
	//getParent()->addChild(bullet6, 2);
}
void Monster::beHit(Vec2 dir)
{
	Person::beHit(dir);
	if(_curLife < 0) return;
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	_progress->setProgress(_curLife * 1.0 / _maxLife * 100);
	_spHit->setVisible(true);
	_spHitTime = 0;
	if(_isDead)
	{
		heroScore += 100*_monsterType*_hard;
		char s[10];
		sprintf(s,"%d",heroScore);
		NotificationCenter::getInstance()->postNotification(showScore,String::create(s));
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
	if(_hard == 3&&hitArea()){
		getPhysicsBody()->setCollisionBitmask(TYPE::MONSTER | TYPE::HERO | TYPE::GROUND | TYPE::TANGH | TYPE::BULLET | TYPE::BOSS | TYPE::PLANK);
		getPhysicsBody()->setContactTestBitmask(TYPE::MONSTER | TYPE::HERO  | TYPE::TANGH | TYPE::BULLET | TYPE::BOSS);
		float tx = getParent()->getChildByTag(TYPE::HERO)->getPositionX() - getPositionX();
		if(tx>0){
			setDir(1);
		}else{
			setDir(-1);
		}
	}
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	setScaleX(getDir() == 1 ? -1 : 1);
	_spHit->setPosition(Vec2(30, 30) );
	if(_spHit->isVisible())
	{
		_spHitTime++;
		if(_spHitTime >= 10) _spHit->setVisible(false);
	}
}
bool Monster::hitArea(){
	auto p = getParent()->getChildByTag(TYPE::HERO)->getPosition() - getPosition();
	return fabs(p.x)<300 && fabs(p.y)<30;
}