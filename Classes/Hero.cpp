#include"Hero.h"
#include "Headfile.h"
using namespace std;
bool Hero::init()
{
	isDead = false;
	_isJump = true;
	_leftDown  = false;
	_rightDown = false;
	_moveState = 0;
	string txt = ("player_1_4.png");
	if (!Sprite::initWithFile(txt))	return false;
	setTag(TYPE::HERO);
	Person::init();
	idle();
	addObserver();
	addListener();
	return true;
}

void Hero::idle()
{    
	//removeAllChildren();
	stopAllActions();
	setSpriteFrame(SpriteFrame::create("player_1_4.png", Rect(0, 0, 57, 63)));
}

void Hero::addListener()
{
	_listen_key = EventListenerKeyboard::create();
	_listen_key->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	_listen_key->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listen_key, this);
}
void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* evt){
	switch(keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
		leftButtonDown(NULL);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
		rightButtonDown(NULL);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE :
		jumpButtonDown(NULL);	
		break;
	}
}
void Hero::leftButtonDown(Object * object){
	setDir(-1);
	_leftDown = true;
}
void Hero::rightButtonDown(Object * object){
	setDir(1);
	_rightDown = true;
}
void Hero::jumpButtonDown(Object * object){
	if(!_isJump){
		_isJump = true;
		getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, 803.0));
	}
}
void Hero::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* evt){
	switch(keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
		leftButtonUp(NULL);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
		rightButtonUp(NULL);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE :  //never have this function!!!!
		//jumpButtonUp();
		break;
	}
}
void Hero::leftButtonUp(Object * object){
	_leftDown = false;
	setDir(_rightDown?1:-1);
}
void Hero::rightButtonUp(Object * object){
	_rightDown = false;
	setDir(_leftDown?-1:1);
}
void Hero::jumpButtonUp(Object * object){
	_isJump = false;
}
void Hero::runAnimation()
{
	log("hehe");
	Vector<SpriteFrame*> allFrames;
	char txt[100];
	for(int i = 1;i <= 6; i++)
	{
		sprintf_s(txt, "player_1_%d.png",i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 57, 63));
		allFrames.pushBack(sf);
	}
	runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
	stopAllActions();
	runAction(RepeatForever::create(Animate::create(runAni)));
}

void Hero::addObserver()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::leftButtonDown), strLeftButtonDown, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::rightButtonDown), strRightButtonDown, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::jumpButtonDown), strJumpButtonDown, NULL);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::leftButtonUp), strLeftButtonUp, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::rightButtonUp), strRightButtonUp, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::jumpButtonUp), strJumpButtonUp, NULL);
}
void Hero::update(float dt)
{
	updateMoveState();	//ÐÎÌ¬¸üÐÂ
	if(_moveState&1){
		getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	}
}

void Hero::updateMoveState(){
	int tmpState = 0;
	if(_leftDown)	tmpState ^= 1;
	if(_rightDown)	tmpState ^= 3;
	if(_isJump)		tmpState ^= 4;
	if(_moveState == tmpState)	return;
	_moveState = tmpState;
	idle();
	if( (_moveState&1) && (!(_moveState&4)))	runAnimation();
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