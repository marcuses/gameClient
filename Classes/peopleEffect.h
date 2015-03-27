#ifndef __PEOPLEEFFECT_H__
#define __PEOPLEEFFECT_H__

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;;

class peopleEffect : public Sprite
{
public:
	static peopleEffect* create();
	virtual bool init();
	void onEnter();
	void update(float dt);
	
private:
	float del_Time;
	float rest_Time;
};

#endif