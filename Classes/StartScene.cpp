#include "StartScene.h"
#include "Author.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "socketClient.h"
#include <vector>
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

	Hero::heroLife = 10;
	heroScore = 0;
	rankScore = 0;

	Size vSize = Director::getInstance()->getVisibleSize();
	auto userName = Label::createWithTTF("123u","fonts/Marker Felt.ttf",20);
	userName->setPosition(0,vSize.height);
	userName->setAnchorPoint(Vec2(0,1));
	addChild(userName,10);

	auto node = CSLoader::createNode("StartScene.csb");
	addChild(node);
	
	auto choiceNode = CSLoader::createNode("ChoiceNode.csb");
	addChild(choiceNode,2);
	choiceNode->setVisible(false);
	auto easyMode = dynamic_cast<ui::Button*>(choiceNode->getChildByName("easyButton"));
	easyMode->addClickEventListener([=](Ref* pSender){
		MainScene::hard  = 1;
		MainScene::level = 1;
		Director::getInstance()->replaceScene(MainScene::createScene()); // change later
	});
	auto midMode = dynamic_cast<ui::Button*>(choiceNode->getChildByName("midButton"));
	midMode->addClickEventListener([=](Ref* pSender){
		MainScene::hard  = 2;
		MainScene::level = 1;
		Director::getInstance()->replaceScene(MainScene::createScene()); // change later
	});
	auto hardMode = dynamic_cast<ui::Button*>(choiceNode->getChildByName("hardButton"));
	hardMode->addClickEventListener([=](Ref* pSender){
		MainScene::hard  = 3;
		MainScene::level = 1;
		Director::getInstance()->replaceScene(MainScene::createScene()); // change later
	});

	auto aboutButton = dynamic_cast<ui::Button*>(node->getChildByName("AboutButton"));
	aboutButton->addClickEventListener([=](Ref* pSender){
		Director::getInstance()->replaceScene(Author::createScene()); 
	});

	auto startButton = dynamic_cast<ui::Button*>(node->getChildByName("StartButton"));
	startButton->addClickEventListener([=](Ref* pSender){
		choiceNode->setVisible(true);
		aboutButton->setVisible(false);
		aboutButton->setVisible(true);
	});

	socketClient st;
	std::vector<NetPacket_Score* > scoreVec;
	st.GetScoreRankList(scoreVec);
	int  n = scoreVec.size();
	char ss[30];
	for(int i=0;i<n;++i){
		sprintf(ss,"%d     %s     %d",i+1,scoreVec[i]->strUserName,scoreVec[i]->nScore);
		auto tmp =  Label::createWithTTF(ss,"fonts/Marker Felt.ttf",15);
		tmp->setPosition(vSize.width/2,vSize.height - (i+1)*30);
		addChild(tmp);
	}
	return true;
}
