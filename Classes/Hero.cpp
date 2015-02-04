#include"Hero.h"
#include "Headfile.h"
using namespace std;
bool Hero::init()
{
	isLeft = false;
	isDead = false;
	isJump = false;
	/*runLeft = false;
	runRight = false;
	runUp = false;
	runDown = false;*/
//	hasBuff = false;
	string txt = ("player_1_4.png");
	if (!Sprite::initWithFile(txt)) {
		return false;
	}
	//key_cnt = 0;
	setType(TYPE::HERO);
	Person::init();
	idle();
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
}

void Hero::goLeft(Object * object)
{
	setDir(-1);
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
}

void Hero::goRight(Object * object)
{
	setDir(1);
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
}

void Hero::Jump(Object * object)
{
	if(!isJump)
	{
		isJump = true;
		getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, 100.0));
	}
}


//void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* evt)
//{
//	switch(keyCode)
//	{
//	case EventKeyboard::KeyCode::KEY_A:
//		isLeft = true;
//		runLeft = true;
//		key_cnt++;
//		if(key_cnt == 1)
//			runAnimation();
//		break;
//	case EventKeyboard::KeyCode::KEY_D: 
//		runRight = true;
//		isLeft = false;
//		key_cnt++;
//		if(key_cnt == 1)
//			runAnimation();
//		break;
//	case EventKeyboard::KeyCode::KEY_W:
//		runUp = true;
//		key_cnt++;	
//		if(key_cnt == 1)
//			runAnimation();
//		break;
//	case EventKeyboard::KeyCode::KEY_S: 
//		runDown = true;
//		key_cnt++;	
//		if(key_cnt == 1)
//			runAnimation();
//		break;
//	default: break;
//	}
//	CCLOG("keycnt = %d",key_cnt);
//}
//
//void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* evt)
//{
//	switch(keyCode)
//	{
//	case EventKeyboard::KeyCode::KEY_A:	
//		runLeft = false;
//		key_cnt--;
//		break;
//	case EventKeyboard::KeyCode::KEY_D: 
//		runRight = false;	
//		key_cnt--;		
//		break;
//	case EventKeyboard::KeyCode::KEY_W:
//		runUp = false;	
//		key_cnt--;		
//		break;
//	case EventKeyboard::KeyCode::KEY_S: 
//		runDown = false;
//		key_cnt--;		
//		break;
//	default: break;
//	}
//	if(key_cnt == 0)
//	{
//		idle();
//	}
//}

void Hero::update(float dt)
{
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