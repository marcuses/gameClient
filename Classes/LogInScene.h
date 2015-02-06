#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__

#include "cocos2d.h"
#include <string>
class LogInScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LogInScene);
private:
	void logInSuccess();
	cocos2d::TextFieldTTF* TextFieldPID;
	cocos2d::TextFieldTTF* TextFieldPSW;
	//Rect rectPID;
	//Rect rectPSW;
	//Rect rectLOG;
};
#endif