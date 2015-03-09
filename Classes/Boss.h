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
	void shoot(Object * object);
	void beHit();
private:
	int _life;
	Sprite* _spHit;
	bool _isdead;
	STATE _curState;
	Sprite* _spWeak;
	ArmatureAnimation* _animation;
	int _monsterType;
	int _time;
};
