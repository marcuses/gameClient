#ifndef __KEYBOARDLISTENER_H__
#define __KEYBOARDLISTENER_H__

#include "cocos2d.h"

class KeyBoardListener : public cocos2d::Layer{
public:
	virtual void onEnter() override;
	virtual void onExit() override;
	void KeyBoardListener::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* evt);
	void KeyBoardListener::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* evt);
	CREATE_FUNC(KeyBoardListener);
private:
	cocos2d::EventListenerKeyboard* listener;
};

#endif
