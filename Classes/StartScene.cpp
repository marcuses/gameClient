#include "StartScene.h"
#include "Author.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "socketClient.h"
#include "Headfile.h"
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
	ShareData::getInstance()->heroScore = 0;
	ShareData::getInstance()->rankScore = 0;

	Size vSize = Director::getInstance()->getVisibleSize();

	auto userName = Label::createWithTTF("aaaa","fonts/Marker Felt.ttf",40);
	userName->setColor(Color3B(255,255,0));
	userName->setPosition(0,vSize.height);
	//userName->setPosition(200,200);
	userName->setAnchorPoint(Vec2(0,1));
	addChild(userName,10);
	char userString[30];
	log("11111111111111111111111111111111111111111111111111111111");
	log(ShareData::getInstance()->heroID.c_str());
	log("11111111111111111111111111111111111111111111111111111111");
	if(!ShareData::getInstance()->isTraveler){
		sprintf(userString,"Welcome to %s",ShareData::getInstance()->heroID.c_str());
		log(userString);
		userName->setString(userString);
	}
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
		sprintf(ss,"%d     \t%s        \t%d",i+1,scoreVec[i]->strUserName,scoreVec[i]->nScore);
		auto tmp =  Label::createWithTTF(ss,"fonts/Marker Felt.ttf",30);
		tmp->setAlignment(TextHAlignment::LEFT);
		tmp->setAnchorPoint(Vec2(0,0));
		tmp->setPosition(vSize.width/3,vSize.height - (i+1)*30);
		addChild(tmp);
	}
	return true;
}
