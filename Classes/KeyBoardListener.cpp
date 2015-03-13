#include "KeyBoardListener.h"
#include "Headfile.h"
USING_NS_CC;

bool KeyBoardListener::init(){
	if(!Layer::init())	return false;
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(KeyBoardListener::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(KeyBoardListener::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	return true;
}
void KeyBoardListener::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* evt){
	switch(keyCode){
	case EventKeyboard::KeyCode::KEY_A :
		NotificationCenter::getInstance()->postNotification(strLeftButtonDown);
		break;
	case EventKeyboard::KeyCode::KEY_D :
		NotificationCenter::getInstance()->postNotification(strRightButtonDown);
		break;
	case EventKeyboard::KeyCode::KEY_K :
		NotificationCenter::getInstance()->postNotification(strJumpButtonDown);
		break;
	case EventKeyboard::KeyCode::KEY_J :
		NotificationCenter::getInstance()->postNotification(strHeroShoot);
		break;
	default: break;
	}
}
void KeyBoardListener::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* evt){
	switch(keyCode){
	case EventKeyboard::KeyCode::KEY_A :
		NotificationCenter::getInstance()->postNotification(strLeftButtonUp);
		break;
	case EventKeyboard::KeyCode::KEY_D :
		NotificationCenter::getInstance()->postNotification(strRightButtonUp);
		break;
	case EventKeyboard::KeyCode::KEY_K :  //never have this function!!!!
		//jumpButtonUp();
		break;
	}
}