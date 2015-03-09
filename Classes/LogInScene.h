#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__
#include "MyTextFieldTTF.h"
#include "cocos2d.h"
class LogInScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void logIn();
    CREATE_FUNC(LogInScene);
private:
	void logInSuccess();
	void logInFail();
	cocos2d::Label* hintMsg;
	MyTextFieldTTF* TextFieldPID;
	MyTextFieldTTF* TextFieldPSW;
};
#endif