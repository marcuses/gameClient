#include "GameOver.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
using namespace cocostudio;
cocos2d::Scene* GameOver::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameOver::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	auto node = CSLoader::createNode("GameOver.csb");
	auto action = CSLoader::createTimeline("GameOver.csb");
	addChild(node);
	node->runAction(action);
	action->gotoFrameAndPlay(0, true);

//	mCheckBoxMusic = dynamic_cast<ui::CheckBox*>(node->getChildByName("CheckBox_Music"));
	//mCheckBoxYinxiao = dynamic_cast<ui::CheckBox*>(node->getChildByName("CheckBox_yinxiao"));
	auto mReturnBtn = dynamic_cast<ui::Button*>(node->getChildByName("Return_Btn"));
	mReturnBtn->addClickEventListener([&](Ref* sender)
	{
		MainScene::level = 1;
		auto nextScene = MainScene::createScene();
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f,nextScene));
	});
//	mAboutBtn = dynamic_cast<ui::Button*>(node->getChildByName("Button_About"));
	return true;
}

