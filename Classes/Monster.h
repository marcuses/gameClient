#pragma  once

#include "cocos2d.h"
#include "Person.h"
#include "Progress.h"
USING_NS_CC;
class Monster : public Person
{
public:
	static Monster* create(int mType);
	bool init(int mType);
	void onEnter();
	void addPhysics();
	void addRunAnimation();
	void updateBullet(float dt);
	void onFrameEvent(Bone *bone,const std::string& evt, int originFrameIndex, int currentFrameIndex); 
	//void deadAnimation();
	void update(float dt);
	void beHit() override;
	void removeThis(float dt);
	void atkToRun(float dt);
private:
	Sprite* _spHit;
	Progress* _progress;
	int _spHitTime;
	int _monsterType;
};
