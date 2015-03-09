#include "LogInScene.h"
#include "MainScene.h"
USING_NS_CC;

Scene* LogInScene::createScene(){
	auto scene = Scene::create();
	auto layer = LogInScene::create();
	scene->addChild(layer);
	return scene;
}
bool LogInScene::init(){
	if(!Layer::init())	return false;
	Size vSize  = Director::getInstance()->getVisibleSize();
	auto bgSprite = Sprite::create("login.png");
	float rateX = vSize.width/bgSprite->getContentSize().width;
	float rateY = vSize.height/bgSprite->getContentSize().height;
	bgSprite->setPosition(vSize/2);
	bgSprite->setScaleX(rateX);
	bgSprite->setScaleY(rateY);
	addChild(bgSprite);

	TextFieldPID = MyTextFieldTTF::myTextFieldWithPlaceHolder(1,"<Input your ID>","fonts/Marker Felt.ttf",20);
	TextFieldPID->setType(1);
	addChild(TextFieldPID);
	TextFieldPID->setPosition(Vec2(300*rateX,205*rateY));
	
	TextFieldPSW = MyTextFieldTTF::myTextFieldWithPlaceHolder(2,"<Input your PassWord>","fonts/Marker Felt.ttf",20);
    TextFieldPSW->setType(2);
	addChild(TextFieldPSW);
	TextFieldPSW->setPosition(Vec2(300*rateX,162*rateY));

	Rect rectPID = Rect(210*rateX,190*rateY,175*rateX,30*rateY);
	Rect rectPSW = Rect(210*rateX,148*rateY,175*rateX,30*rateY);
	Rect rectLOG = Rect(210*rateX,109*rateY,175*rateX,30*rateY);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* evt){
		if( rectPID.containsPoint(touch->getLocation())){
			log("PID");
			TextFieldPID->attachWithIME();
			TextFieldPID->getString();
			
			//TextFieldPID->setOn(true);
			TextFieldPSW->detachWithIME();
			//TextFieldPSW->setOn(false);
		}else if( rectPSW.containsPoint(touch->getLocation()) ){
			log("PSW");
			TextFieldPSW->attachWithIME();
			//TextFieldPSW->setOn(true);
			TextFieldPID->detachWithIME();
			//TextFieldPID->setOn(false);
		}else if( rectLOG.containsPoint(touch->getLocation()) ){
			log("SUCCESS");
			logInSuccess();
		}else{
			TextFieldPID->detachWithIME();
			//TextFieldPID->setOn(false);
			TextFieldPSW->detachWithIME();
			//TextFieldPSW->setOn(false);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void LogInScene::logInSuccess(){
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
