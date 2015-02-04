#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Person : public Sprite
{
public:
	CREATE_FUNC(Person);
	virtual bool init();
	virtual void addRunAnimation();
	virtual void addPhysics();
	//	void addObserver();

	void setSpeed(float speed);
	float getSpeed();
	void setType(TYPE type);
	TYPE getType();
	int getDir();
	void setDir(int dir);

	void deadAnimation();
	void changeDir(); // 改变方向
	//float getHealth(){ return health; }
	//void setHealth(float h){ health = h; }
private:
	int _dir; //指示方向
	TYPE _type;
	float _speed;
};
