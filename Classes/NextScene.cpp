#include "NextScene.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
using namespace cocostudio;
cocos2d::Scene* NextScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = NextScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool NextScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	auto node = CSLoader::createNode("NextScene.csb");
	addChild(node);
	auto mNextBtn = dynamic_cast<ui::Button*>(node->getChildByName("Button_Next"));
	mNextBtn->addClickEventListener([&](Ref* sender)
	{
		Director::getInstance()->replaceScene(TransitionFadeTR::create(2.0f, MainScene::createScene()));
	});
	return true;
}