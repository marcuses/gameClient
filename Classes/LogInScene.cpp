#include "LogInScene.h"
#include "StartScene.h"
#include "RegisterScene.h"
#include "socketClient.h"
USING_NS_CC;

Scene* LogInScene::createScene(){
	auto scene = Scene::create();
	auto layer = LogInScene::create();
	scene->addChild(layer);
	return scene;
}
void LogInScene::onEnter(){
	Layer::onEnter();
	Size vSize  = Director::getInstance()->getVisibleSize();
	auto bgSprite = Sprite::create("login.png");
	float rateX = vSize.width/bgSprite->getContentSize().width;
	float rateY = vSize.height/bgSprite->getContentSize().height;

	log("%f %f",rateX,rateY);
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

	hintMsg = Label::createWithTTF("","fonts/Marker Felt.ttf",20);
	addChild(hintMsg);
	hintMsg->setTextColor(Color4B(138,43,226,255));
	hintMsg->setPosition(Vec2(300*rateX,70*rateY));

	Rect rectPID = Rect(210*rateX,190*rateY,175*rateX,30*rateY);
	Rect rectPSW = Rect(210*rateX,148*rateY,175*rateX,30*rateY);
	Rect rectLOG = Rect(310*rateX,109*rateY,75*rateX,30*rateY);
	Rect rectFLOG= Rect(210*rateX,109*rateY,75*rateX,30*rateY);
	Rect rectREG = Rect(414*rateX,150*rateY,32*rateX,62*rateY);


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* evt){
		log("%f %f",touch->getLocation().x,touch->getLocation().y);
		hintMsg->setString("");
		if( rectPID.containsPoint(touch->getLocation())){
			log("PID");
			TextFieldPID->attachWithIME();
			TextFieldPSW->detachWithIME();
		}else if( rectPSW.containsPoint(touch->getLocation()) ){
			log("PSW");
			TextFieldPSW->attachWithIME();
			TextFieldPID->detachWithIME();
		}else if( rectLOG.containsPoint(touch->getLocation()) ){
			log("SUCCESS");
			logIn();
		}else if(rectFLOG.containsPoint(touch->getLocation()) ){
			log("FastLogIn");
			logInSuccess();
		}else if( rectREG.containsPoint(touch->getLocation()) ){
			log("Register");
			Director::getInstance()->replaceScene(RegisterScene::createScene());
		}else{
			TextFieldPID->detachWithIME();
			TextFieldPSW->detachWithIME();
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}
void LogInScene::onExit(){
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}
void LogInScene::logIn(){
	socketClient test;
	if(test.LoginSendData(TextFieldPID->getString(),TextFieldPSW->getString(),2)) logInSuccess();
	else	logInFail();
}
void LogInScene::logInSuccess(){
	log(TextFieldPID->getString().c_str());
	log(TextFieldPSW->getString().c_str());
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void LogInScene::logInFail(){
	TextFieldPSW->setString("");
	hintMsg->setString("Incorrect ID or password");
}
