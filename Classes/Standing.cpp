#include "Standing.h"
#include "MainScene.h"
USING_NS_CC;

Scene* Standing::createScene(){
    auto scene = Scene::create();
    
	auto layer = Standing::create();

    scene->addChild(layer);

    return scene;
}

bool Standing::init(){
    if(!Layer::init())	 return false;

	Size vSize = Director::getInstance()->getVisibleSize();

	auto bgSprite	= Sprite::create("Splash.png");
	addChild(bgSprite);
	bgSprite->ignoreAnchorPointForPosition(true);
	auto standingLabel	= Label::createWithTTF("Standing", "fonts/Marker Felt.ttf", 50);
	standingLabel->setPosition(vSize.width/2,540);
	addChild(standingLabel);
	char tmpFirst[20],tmpSecond[20],tmpThird[20];
	auto firstScore =  UserDefault::getInstance()->getIntegerForKey("firstScore",0);
	auto secondScore=  UserDefault::getInstance()->getIntegerForKey("secondScore",0);
	auto thirdScore =  UserDefault::getInstance()->getIntegerForKey("thirdScore",0);
	sprintf(tmpFirst,"FirstScore:    %d",firstScore);
	sprintf(tmpSecond,"SecondScore:  %d",secondScore);
	sprintf(tmpThird,"ThirdScore:    %d",thirdScore);
	auto firstLabel	= Label::createWithTTF(tmpFirst, "fonts/Marker Felt.ttf", 40);
	firstLabel->setPosition(vSize.width/2,450);
	addChild(firstLabel);

	auto secondLabel	= Label::createWithTTF(tmpSecond, "fonts/Marker Felt.ttf", 40);
	secondLabel->setPosition(vSize.width/2,350);
	addChild(secondLabel);
	
	auto thirdLabel	= Label::createWithTTF(tmpThird, "fonts/Marker Felt.ttf", 40);
	thirdLabel->setPosition(vSize.width/2,250);
	addChild(thirdLabel);
    
	auto backMenu = MenuItemImage::create("ui/back.png","ui/back.png",[](Ref* pSender){
		auto scene	=MainScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	backMenu->setPosition(0,0);
	backMenu->ignoreAnchorPointForPosition(true);
	auto menu = Menu::create(backMenu,NULL);
	addChild(menu);
	menu->setPosition(0,0);
	return true;
}



