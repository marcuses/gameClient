#ifndef __UICTRL_H__
#define __UICTRL_H__

#include "cocos2d.h"

class UICtrl : public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(UICtrl);
private:
	cocos2d::Sprite* stop;
	cocos2d::Sprite* back;
	cocos2d::Sprite* quit;
	cocos2d::Layer* _myCtrlLayer;
	void showLayer();
	void hideLayer();
};

#endif