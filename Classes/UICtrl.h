#ifndef __UICTRL_H__
#define __UICTRL_H__

#include "cocos2d.h"

class UICtrl : public cocos2d::Layer{
public:
	virtual void onEnter() override;
	virtual void onExit() override;
	CREATE_FUNC(UICtrl);
private:
	cocos2d::Layer*  playLayer;
	cocos2d::Layer*  stopLayer;	
	cocos2d::Sprite* moveButton;

	cocos2d::Layer*  dieLayer;

	void showLayer();
	void hideLayer();
	void dieShow(cocos2d::Object* obj);
	void showBuff(cocos2d::Object* obj);
	void hideBuff(cocos2d::Object* obj);
	
	cocos2d::EventListenerTouchOneByOne* listener;
};

#endif