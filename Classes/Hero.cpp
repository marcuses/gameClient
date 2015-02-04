#include"Hero.h"
#include "Headfile.h"
using namespace std;
bool Hero::init()
{
	isDead = false;
	_isJump = false;
	_isRunning = false;
	/*runLeft = false;
	runRight = false;
	runUp = false;
	runDown = false;*/
//	hasBuff = false;
	string txt = ("player_1_4.png");
	//Sprite::create(txt);
	if (!Sprite::initWithFile(txt)) {
	return false;
	}
	//key_cnt = 0;
	setType(TYPE::HERO);
	Person::init();
	idle();
	addObserver();
	//addListener();
	return true;
}

void Hero::idle()
{    
	//removeAllChildren();
	stopAllActions();
	setSpriteFrame(SpriteFrame::create("player_1_4.png", Rect(0, 0, 57, 63)));
	//key_cnt = 0;
}

//void Hero::addListener()
//{
//	_listen_key = EventListenerKeyboard::create();
//	_listen_key->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
//	_listen_key->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listen_key, this);
//}
void Hero::runAnimation()
{
	Vector<SpriteFrame*> allFrames;
	char txt[100];
	for(int i = 1;i <= 6; i++)
	{
		sprintf_s(txt, "player_1_%d.png",i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 57, 63));
		allFrames.pushBack(sf);
	}
	runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
	runAction(RepeatForever::create(Animate::create(runAni)));
}

void Hero::addObserver()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::goLeft), strGoLeft, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::goRight), strGoRight, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::Jump), strJump, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::StopAction), strStop, NULL);
}

void Hero::goLeft(Object * object)
{
	setDir(-1);
	_isRunning = true;
	runAnimation();
	//getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
}

void Hero::goRight(Object * object)
{
	setDir(1);
	_isRunning = true;
	runAnimation();
	//getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
}

void Hero::Jump(Object * object)
{
	if(!_isJump)
	{
		_isJump = true;
		getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, 500.0));
	}
}

void Hero::StopAction(Object* object)
{
	_isRunning = false;
}
void Hero::update(float dt)
{
	if(_isRunning)
	{
		getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	}
	else
	{
		stopAllActions();
	}
	setScaleX(getDir() == 1 ? 1 : -1);
}

void Hero::dead()
{
	stopAllActions();
//	removeAllChildren();
	isDead = true;
	_eventDispatcher->removeEventListener(_listen_key);
	setSpriteFrame(SpriteFrame::create("player_2.png", Rect(0, 0, 63, 63)));
}