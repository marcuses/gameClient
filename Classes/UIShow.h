#ifndef __UISHOW_H__
#define __UISHOW_H__

#include "cocos2d.h"

class UIShow : public cocos2d::Layer{
public:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(float dt) override;
	CREATE_FUNC(UIShow);
	float getTime();
	void setLife(cocos2d::Object* object);
private:
	cocos2d::Sprite* lifeSprite;
	cocos2d::Label* curLife;
	cocos2d::Label* curTime;
	float runTime;
};

#endif