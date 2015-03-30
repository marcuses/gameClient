#ifndef __UISHOW_H__
#define __UISHOW_H__

#include "cocos2d.h"

class UIShow : public cocos2d::Layer{
public:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	void update(float dt);
	CREATE_FUNC(UIShow);
	void setLife(cocos2d::Object* object);
	void setScore(cocos2d::Object* object);
	float getTime();
private:
	cocos2d::Label* curLife;
	cocos2d::Label* curTime;
	cocos2d::Label* curScore;
	float runTime;
};

#endif