#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Buff : public Sprite
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(int type);
	static Buff* create(int type);
	inline int getType(){ return _type; }
private:
	int _type;
};


