#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
#include"cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocostudio;
USING_NS_CC;

class Person : public Sprite
{
public:
	static Person* create(int maxLife);
	virtual bool init(int maxLife);
	virtual void addRunAnimation();
	virtual void addPhysics();
	//	void addObserver();

	void setSpeed(float speed);
	float getSpeed();
	void setType(TYPE type);
	TYPE getType();
	int getDir();
	void setDir(int dir);
	virtual void beHit();
	void deadAnimation();
	void changeDir(); // 改变方向
	//float getHealth(){ return health; }
	//void setHealth(float h){ health = h; }
protected:
	bool _isDead;
	int _curLife;
	int _maxLife;
private:
	int _dir; //指示方向
	TYPE _type;
	float _speed;
};
