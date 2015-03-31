#pragma once
#include "cocos2d.h"

USING_NS_CC;

class dynamicTrap : public Sprite
{
public:
	static dynamicTrap* create(const char *imgname);
	virtual bool init(const char *imgname);
	void update(float dt);
private:
	bool _isFire;
};


