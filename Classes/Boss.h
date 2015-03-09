#pragma  once

#include "cocos2d.h"
#include "Person.h"
USING_NS_CC;
enum STATE
{
	walk, shoot, addMonster
};
class Boss : public Person
{
public:
	CREATE_FUNC(Boss);
	bool init();
	void addRunAnimation();
	//void deadAnimation();
	void update(float dt);
private:
	STATE _curState;
	ArmatureAnimation* _animation;
	int _monsterType;
	int _time;
};
