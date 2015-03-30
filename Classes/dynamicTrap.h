#pragma once
#include "cocos2d.h"

USING_NS_CC;

class dynamicTrap : public Sprite
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	CREATE_FUNC(dynamicTrap);
	void update(float dt);
};


