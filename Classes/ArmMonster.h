#pragma  once

#include "cocos2d.h"
#include "ArmPerson.h"
USING_NS_CC;

class ArmMonster : public ArmPerson
{
public:
	CREATE_FUNC(ArmMonster);
	bool init();
	void addRunAnimation();
	//void deadAnimation();
	void update(float dt);
private:
	int _monsterType;
};
