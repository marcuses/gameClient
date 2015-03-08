#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
#include"cocostudio/CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

class ArmPerson : public Armature
{
public:
	CREATE_FUNC(ArmPerson);
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
