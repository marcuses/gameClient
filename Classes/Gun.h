#pragma  once

#include "cocos2d.h"
#include "Person.h"
#include "Progress.h"
USING_NS_CC;
class Gun : public Person
{
public:
	static Gun* create(int mhard);
	bool init(int mhard);
	void onEnter();
	void addPhysics();
	void updateBullet(float dt);
	void addRunAnimation();
	void update(float dt);
	void beHit() override;
	void removeThis(float dt);
	void AIeasy();
	void AImid();
	void AIhard();
private:
	Sprite* _spHit;
	Progress* _progress;
	int _spHitTime;
	int _monsterType;
	int _hard;
	bool outScene();
};
