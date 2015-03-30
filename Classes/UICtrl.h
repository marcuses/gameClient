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
	cocos2d::Layer* stopLayer;	
	void showLayer();
	void hideLayer();
	cocos2d::EventListenerTouchOneByOne* listener;
};

#endif