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
	cocos2d::Sprite* leftButton;
	cocos2d::Sprite* rightButton;
	cocos2d::Sprite* jumpButton;
	cocos2d::Sprite* fireButton;
	cocos2d::Sprite* stopButton;

	cocos2d::Layer* stopLayer;
	cocos2d::Sprite* backButton;
	cocos2d::Sprite* restartButton;
	cocos2d::Sprite* quitButton;
	
	void showLayer();
	void hideLayer();

	cocos2d::EventListenerTouchOneByOne* listener;
};

#endif