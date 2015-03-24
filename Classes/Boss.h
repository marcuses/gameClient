#pragma  once

#include "cocos2d.h"
#include "Person.h"
#include "Progress.h"
USING_NS_CC;

class Boss : public Person
{
public:
	static Boss* create(int mhard);
	bool init(int mhard);
	void onEnter();
	void addRunAnimation();
	//void deadAnimation();
	void update(float dt);
	void shoot(Object * object);
	void beHit() override;
	void AIeasy();
	void AImid();
	void AIhard();
private:
	Sprite* _spHit;
	Progress* _progress;
	int _spHitTime;
	STATE _curState;
	Sprite* _spWeak;
	int _monsterType;
	int _time;
	int _hard;
};
