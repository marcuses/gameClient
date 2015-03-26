#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;;
class peopleEffect : public Sprite
{
public:
	static peopleEffect* create();
	
	virtual bool init();
	void onEnter();
	void update(float dt) override;
	
private:
	int del_Time;
	int rest_Time;
};
