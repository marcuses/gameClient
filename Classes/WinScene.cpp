#include "WinScene.h"
#include "LogInScene.h"
#include "StartScene.h"
#include "ui/UIButton.h"
#include "socketClient.h"
#include "Headfile.h"
using namespace cocostudio;
cocos2d::Scene* WinScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WinScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool WinScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	auto node = CSLoader::createNode("WinScene.csb");
	auto action = CSLoader::createTimeline("WinScene.csb");
	node->runAction(action);
	action->gotoFrameAndPlay(0, true);
	addChild(node);
	
	socketClient test;
	if(!ShareData::getInstance()->isTraveler)	test.LoginSendData(ShareData::getInstance()->heroID,ShareData::getInstance()->heroPSW,SCORE_CODE,ShareData::getInstance()->rankScore);
	
	char ss[10];
	sprintf(ss,"%d",ShareData::getInstance()->rankScore);
	auto tmp =  Label::createWithTTF(ss,"fonts/Marker Felt.ttf",50);
	tmp->setPosition(642,536);
	tmp->setColor(Color3B(238,174,238));

	addChild(tmp);

	auto mBackBtn = dynamic_cast<ui::Button*>(node->getChildByName("Button_Back"));
	mBackBtn->addClickEventListener([&](Ref* sender)
	{
		auto nextScene = StartScene::createScene();
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f,nextScene));
	});
	return true;
}