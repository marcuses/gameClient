#ifndef __NEWLOGIN_H__
#define __NEWLOGIN_H__

#include "cocos2d.h"
#include <string>
class NewLogIn : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(NewLogIn);
private:
	void logIn();
	void logInSuccess();
	cocos2d::TextFieldTTF* TextFieldPID;
	cocos2d::TextFieldTTF* TextFieldPSW;
	//Rect rectPID;
	//Rect rectPSW;
	//Rect rectLOG;
};
#endif