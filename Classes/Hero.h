#pragma once
#include "cocos2d.h"
#include "Person.h"
USING_NS_CC;

class Hero : public Person
{
public:


	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	//   void replaceCloseCallback(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(Hero);

	void update(float delta);

	void idle();

	void addObserver();
	//void addListener();

	//void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* evt);
	
	//void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* evt);

	void runAnimation();
	void dead();

	void goLeft(Object * object);
	void goRight(Object * object);
	void Jump(Object * object);
	void StopAction(Object * object);
	/*bool isRunLeft(){ return runLeft;}
	bool isRunRight(){ return runRight;}
	bool isRunUp(){ return runUp;}
	bool isRunDown(){ return runDown;}*/

	bool getBuff(){ return hasBuff; }
	void setBuff(){hasBuff = true;}
	bool isDead; // «∑ÒÀ¿Õˆ
	void setJump(bool isJump){ _isJump = isJump;}
private:
	bool _isRunning;
	//int key_cnt;
	/*bool runLeft;
	bool runRight;
	bool runUp;
	bool runDown;*/
	bool _isJump;
	bool hasBuff;
	Animation* runAni;
	EventListenerKeyboard* _listen_key;
};


