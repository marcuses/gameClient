#ifndef __UICTRL_H__
#define __UICTRL_H__

#include "cocos2d.h"
USING_NS_CC;
class UICtrl : public cocos2d::Layer{
public:
	virtual bool init();
	void onEnter();
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
};

#endif