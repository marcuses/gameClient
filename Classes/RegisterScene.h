#ifndef __REGISTERSCENE_H__
#define __REGISTERSCENE_H__
#include "MyTextFieldTTF.h"
#include "cocos2d.h"
class RegisterScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void registerID();
    CREATE_FUNC(RegisterScene);
private:
	void registerSuccess();
	void registerFail();
	void invalidPSW();
	void wrongPSW();
	cocos2d::Label* hintMsg;
	MyTextFieldTTF* TextFieldPID;
	MyTextFieldTTF* TextFieldPSW;
	MyTextFieldTTF* TextFieldPSWS;
};
#endif