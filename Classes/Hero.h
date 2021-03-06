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
	void onEnter();
	void onExit();
	void update(float delta);
	void quickMove(Object * object);
	void quickMoveEnd(float dt);
	void idle();

	void addObserver();
	void leftButtonDown(Object * object);
	void rightButtonDown(Object * object);
	void jumpButtonDown(Object * object);

	void leftButtonUp(Object * object);
	void rightButtonUp(Object * object);
	void jumpButtonUp(Object * object);
	void shoot(Object * object);
	void runAnimation();
	void dead();
	void beHit(Vec2 dir) override;
	inline bool getBuff(){ return _hasBuff; }
	inline void setBuff(bool hasBuff){ _hasBuff = hasBuff; }
	inline void setJump(bool isJump){ _isJump = isJump;}
	void addLife();
	static int heroLife;
private:
	Sprite* _spHit;
	bool _invincible; //�Ƿ��޵�
	int _invincibleTime;
	int _spHitTime;
	void possLifeMsg();
	void updateMoveState();
	int _moveState;
	float bulletRate;
	std::string userName;
	bool _isQuickMove;
	int _tolTime;
	int _quickMoveTime;
	bool _leftDown;
	bool _rightDown;
	bool _isJump;
	bool _hasBuff;
	Animation* runAni;
	EventListenerKeyboard* _listen_key;
};


