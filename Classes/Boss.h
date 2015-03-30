#pragma  once

#include "cocos2d.h"
#include "Person.h"
#include "Progress.h"
USING_NS_CC;

class Boss : public Person
{
public:
	static Boss* create(int bossType, int mhard);
	bool init(int bossType, int mhard);
	void onEnter();
	void addRunAnimation();
	//void deadAnimation();
	void update(float dt);
	void shoot(Object * object);
	void beHit(Vec2 dir) override;
	void AIeasy();
	void AImid();
	void AIhard();
private:
	Sprite* _spHit;
	Progress* _progress;
	int _spHitTime;
	STATE _curState;
	Sprite* _spWeak;
	int _bossType;
	int _time;
	int _hard;
};
