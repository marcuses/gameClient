#pragma once
#include "cocos2d.h"
#include "Person.h"
#include "string.h"
#include "Bullet.h"
USING_NS_CC;

class Hero : public Person
{
public:
	virtual bool init();
	CREATE_FUNC(Hero);

	void update(float delta);

	void idle();

	void addObserver();
	void addListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* evt);
	void leftButtonDown(Object * object);
	void rightButtonDown(Object * object);
	void jumpButtonDown(Object * object);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* evt);
	void leftButtonUp(Object * object);
	void rightButtonUp(Object * object);
	void jumpButtonUp(Object * object);
	void shoot(Object * object);
	void runAnimation();
	void dead();

	bool getBuff(){ return hasBuff; }
	void setBuff(){hasBuff = true;}
	bool isDead; // «∑ÒÀ¿Õˆ
	void setJump(bool isJump){ _isJump = isJump;}
	
private:
	void updateMoveState();
	int _moveState;
	std::string userName;
	bool _leftDown;
	bool _rightDown;
	bool _isJump;
	bool hasBuff;
	Animation* runAni;
	EventListenerKeyboard* _listen_key;
};


