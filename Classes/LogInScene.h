#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__
#include "MyTextFieldTTF.h"
#include "cocos2d.h"
#include <string>
class LogInScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LogInScene);
private:
	void logInSuccess();
	MyTextFieldTTF* TextFieldPID;
	MyTextFieldTTF* TextFieldPSW;
};
#endif