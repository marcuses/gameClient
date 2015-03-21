#include "RegisterScene.h"
#include "LogInScene.h"
#include "socketClient.h"
USING_NS_CC;

Scene* RegisterScene::createScene(){
	auto scene = Scene::create();
	auto layer = RegisterScene::create();
	scene->addChild(layer);
	return scene;
}
bool RegisterScene::init(){
	if(!Layer::init())	return false;
	Size vSize  = Director::getInstance()->getVisibleSize();
	auto bgSprite = Sprite::create("register.png");
	float rateX = vSize.width/bgSprite->getContentSize().width;
	float rateY = vSize.height/bgSprite->getContentSize().height;
	bgSprite->setPosition(vSize/2);
	bgSprite->setScaleX(rateX);
	bgSprite->setScaleY(rateY);
	addChild(bgSprite);

	TextFieldPID = MyTextFieldTTF::myTextFieldWithPlaceHolder(1,"<Input your ID>","fonts/Marker Felt.ttf",20);
	addChild(TextFieldPID);
	TextFieldPID->setPosition(Vec2(300*rateX,205*rateY));
	
	TextFieldPSW = MyTextFieldTTF::myTextFieldWithPlaceHolder(2,"<Input your PassWord>","fonts/Marker Felt.ttf",20);
	addChild(TextFieldPSW);
	TextFieldPSW->setPosition(Vec2(300*rateX,162*rateY));

	TextFieldPSWS = MyTextFieldTTF::myTextFieldWithPlaceHolder(2,"<Confirm your PassWord>","fonts/Marker Felt.ttf",20);
	addChild(TextFieldPSWS);
	TextFieldPSWS->setPosition(Vec2(300*rateX,125*rateY));
	
	hintMsg = Label::createWithTTF("","fonts/Marker Felt.ttf",20);
	addChild(hintMsg);
	hintMsg->setTextColor(Color4B(138,43,226,255));
	hintMsg->setPosition(Vec2(300*rateX,60*rateY));

	Rect rectPID = Rect(210*rateX,190*rateY,175*rateX,30*rateY);
	Rect rectPSW = Rect(210*rateX,148*rateY,175*rateX,30*rateY);
	Rect rectPSWS = Rect(210*rateX,109*rateY,175*rateX,30*rateY);
	Rect rectREG = Rect(422*rateX,105*rateY,97*rateX,48*rateY);
	Rect rectBACK = Rect(422*rateX,162*rateY,97*rateX,50*rateY);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* evt){
		log("%f %f",touch->getLocation().x,touch->getLocation().y);
		hintMsg->setString("");
		if( rectPID.containsPoint(touch->getLocation())){
			log("PID");
			TextFieldPID->attachWithIME();
			TextFieldPSW->detachWithIME();
			TextFieldPSWS->detachWithIME();
		}else if( rectPSW.containsPoint(touch->getLocation()) ){
			log("PSW");
			TextFieldPSW->attachWithIME();
			TextFieldPSWS->detachWithIME();
			TextFieldPID->detachWithIME();
		}else if( rectPSWS.containsPoint(touch->getLocation()) ){
			log("PSWS");
			TextFieldPSWS->attachWithIME();
			TextFieldPSW->detachWithIME();
			TextFieldPID->detachWithIME();
		}else if( rectREG.containsPoint(touch->getLocation()) ){
			log("Register");
			if(TextFieldPSW->getString().size()<3)	invalidPSW();
			else if(TextFieldPSW->getString() == TextFieldPSWS->getString())	registerID();
			else wrongPSW();
		}else if(rectBACK.containsPoint(touch->getLocation()) ){
			Director::getInstance()->replaceScene(LogInScene::createScene());
		}else{
			TextFieldPID->detachWithIME();
			TextFieldPSW->detachWithIME();
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void RegisterScene::registerID(){
	socketClient test;
	if(test.LoginSendData(TextFieldPID->getString(),TextFieldPSW->getString(),1)) registerSuccess();
	else	registerFail();
}
void RegisterScene::registerSuccess(){
	auto scene = LogInScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void RegisterScene::wrongPSW(){
	TextFieldPSW->setString("");
	TextFieldPSWS->setString("");
	hintMsg->setString("passwords don\'t match");
}
void  RegisterScene::invalidPSW(){
	TextFieldPSW->setString("");
	TextFieldPSWS->setString("");
	hintMsg->setString("passwords is invalid");
}
void RegisterScene::registerFail(){
	TextFieldPID->setString("");
	TextFieldPSW->setString("");
	TextFieldPSWS->setString("");
	hintMsg->setString("The ID has been registered before");
}
