#pragma  once

#include "cocos2d.h"
#include "Person.h"
USING_NS_CC;

class Monster : public Person
{
public:
	CREATE_FUNC(Monster);
	bool init();
	void addRunAnimation();
	//void deadAnimation();
	void update(float dt);
private:
	int _monsterType;
};
