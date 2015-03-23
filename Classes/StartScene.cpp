#include "StartScene.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace cocostudio;

Scene* StartScene::createScene(){
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init(){
	if ( !Layer::init() )	return false;
	Size vSize = Director::getInstance()->getVisibleSize();
	auto userName = Label::createWithTTF("123u","fonts/Marker Felt.ttf",20);
	userName->setPosition(0,vSize.height);
	userName->setAnchorPoint(Vec2(0,1));
	addChild(userName,10);

	auto node = CSLoader::createNode("StartScene.csb");
	addChild(node);
	
	auto startButton = dynamic_cast<ui::Button*>(node->getChildByName("StartButton"));
	startButton->addClickEventListener([=](Ref* pSender){
		MainScene::level = 1;
		Director::getInstance()->replaceScene(MainScene::createScene());
	});

	auto aboutButton = dynamic_cast<ui::Button*>(node->getChildByName("AboutButton"));
	aboutButton->addClickEventListener([=](Ref* pSender){
		MainScene::level = 1;
		Director::getInstance()->replaceScene(MainScene::createScene()); // change later
	});
	return true;
}
