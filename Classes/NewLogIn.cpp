#include "NewLogIn.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "ui/UITextField.h"
using namespace cocostudio;
USING_NS_CC;


Scene* NewLogIn::createScene(){
	auto scene = Scene::create();
	auto layer = NewLogIn::create();
	scene->addChild(layer);
	return scene;
}

bool NewLogIn::init(){
	if(!Layer::init())	return false;
	
	auto node = CSLoader::createNode("logIn.csb");
	addChild(node);

	auto logInButton = dynamic_cast<ui::Button*>(node->getChildByName("logInButton"));
	logInButton->addClickEventListener([=](Ref* pSender){
		log("hehe");
		logIn();
	});

	auto signUpButton = dynamic_cast<ui::Button*>(node->getChildByName("signUpButton"));
	signUpButton->addClickEventListener([=](Ref* pSender){
		log("hehe");
		logInSuccess();
	});

	auto forgetButton = dynamic_cast<ui::Button*>(node->getChildByName("forgetButton"));
	forgetButton->addClickEventListener([=](Ref* pSender){
		//logInSuccess();
		log("hehe");
	});
	auto tmpPID = dynamic_cast<ui::Button*>(node->getChildByName("logInPID"));
	auto tmpPSW = dynamic_cast<ui::Button*>(node->getChildByName("logInPSW"));

	auto otmp = tmpPID->getPosition();
	Rect rectPID = Rect(otmp.x-50,otmp.y-20,100,40);
	TextFieldPID = TextFieldTTF::textFieldWithPlaceHolder("<Input your ID>","fonts/Marker Felt.ttf",20);
    addChild(TextFieldPID);
	TextFieldPID->setPosition(otmp);
	TextFieldPID->setColor(Color3B(0,255,255));
	TextFieldPID->attachWithIME();

	otmp = tmpPSW->getPosition();
	Rect rectPSW = Rect(otmp.x-50,otmp.y-20,100,40);
	TextFieldPSW = TextFieldTTF::textFieldWithPlaceHolder("<Input your PassWord>","fonts/Marker Felt.ttf",20);
    addChild(TextFieldPSW);
	TextFieldPSW->setPosition(otmp);
	TextFieldPSW->setColor(Color3B(0,255,255));
	TextFieldPSW->detachWithIME();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* evt){
		log("%f %f %f %f",rectPID.origin.x,rectPID.origin.y,rectPID.size.width,rectPID.size.height);
		log("%f %f %f %f",rectPSW.origin.x,rectPSW.origin.y,rectPSW.size.width,rectPSW.size.height);
		log("%f %f",touch->getLocation().x,touch->getLocation().y);
		if( rectPID.containsPoint(touch->getLocation())){
			log("PID");
			TextFieldPID->attachWithIME();
			TextFieldPSW->detachWithIME();
		}else if( rectPSW.containsPoint(touch->getLocation()) ){
			log("PSW");
			TextFieldPSW->attachWithIME();
			TextFieldPID->detachWithIME();
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
void NewLogIn::logIn(){
	//if(LoginSendData(TextFieldPID->getString(),TextFieldPID->getString(),2)) logInSuccess();
	if(1)	logInSuccess();
	else	logInFail();
}
void NewLogIn::logInSuccess(){
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void NewLogIn::logInFail(){
	TextFieldPID->setString("");
	TextFieldPSW->setString("");
}


