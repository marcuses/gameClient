#include "UICtrl.h"
#include "Headfile.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "LogInScene.h"
#include "MainScene.h"
#include "StartScene.h"

USING_NS_CC;

void UICtrl::onEnter(){
	Layer::onEnter();
	auto vSize = Director::getInstance()->getVisibleSize();

	playLayer = Layer::create();
	playLayer->setCascadeOpacityEnabled(true);
	playLayer->setOpacity(GLubyte(255*0.6));
	addChild(playLayer,10);

	auto stopButton = Sprite::create("stopButton.png");
	stopButton->setPosition(vSize);
	stopButton->setAnchorPoint(Vec2(1.0f,1.0f));
	playLayer->addChild(stopButton);

	auto leftButton = Sprite::create("leftButton.png");
	leftButton->setPosition(Vec2(0,0));
	leftButton->setAnchorPoint(Vec2(0,0));
	playLayer->addChild(leftButton);

	auto rightButton = Sprite::create("rightButton.png");
	rightButton->setPosition(Vec2(100,0));
	rightButton->setAnchorPoint(Vec2(0,0));
	playLayer->addChild(rightButton);

	moveButton = Sprite::create("moveButton2.png");
	moveButton->setPosition(Vec2(780,0));
	moveButton->setAnchorPoint(Vec2(1,0));
	playLayer->addChild(moveButton);

	NotificationCenter::getInstance()->addObserver(this, 
		callfuncO_selector(UICtrl::showBuff), strShowBuff, NULL);
	NotificationCenter::getInstance()->addObserver(this, 
		callfuncO_selector(UICtrl::hideBuff), strHideBuff, NULL);
	NotificationCenter::getInstance()->addObserver(this, 
		callfuncO_selector(UICtrl::dieShow), strDieShow, NULL);

	auto hitButton = Sprite::create("hitButton.png");
	hitButton->setPosition(Vec2(870,0));
	hitButton->setAnchorPoint(Vec2(1,0));
	playLayer->addChild(hitButton);

	auto jumpButton = Sprite::create("jumpButton.png");
	jumpButton->setPosition(Vec2(960,0));
	jumpButton->setAnchorPoint(Vec2(1,0));
	playLayer->addChild(jumpButton);

	stopLayer = Layer::create();
	stopLayer->setCascadeOpacityEnabled(true);
	stopLayer->setOpacity(GLubyte(255*0.75));
	stopLayer->setScale(0.5);
	addChild(stopLayer,8);
	stopLayer->setVisible(false);
	
	auto node = CSLoader::createNode("GameStop.csb");
	stopLayer->addChild(node);
	auto backButton = dynamic_cast<ui::Button*>(node->getChildByName("backButton"));
	backButton->addClickEventListener([=](Ref* pSender){
		hideLayer();
	});
	auto restartButton = dynamic_cast<ui::Button*>(node->getChildByName("restartButton"));
	restartButton->addClickEventListener([=](Ref* pSender){
		Hero::heroLife = 10;
		ShareData::getInstance()->heroScore = 0;
		Director::getInstance()->replaceScene(MainScene::createScene());
		Director::getInstance()->resume();
	});
	auto quitButton = dynamic_cast<ui::Button*>(node->getChildByName("quitButton"));
	quitButton->addClickEventListener([=](Ref* pSender){
		Director::getInstance()->replaceScene(StartScene::createScene());
		Director::getInstance()->resume();
	});

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* e){
		if( stopButton->getBoundingBox().containsPoint(touch->getLocation())){
			showLayer();
		}else if( leftButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strLeftButtonDown);
		}else if( rightButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strRightButtonDown);
		}else if( moveButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strQuickMove);
		}else if( hitButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strHeroShoot);
		}else if( jumpButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strJumpButtonDown);
		}
		return true;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* e){
		if( leftButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strLeftButtonUp);
		}else if( rightButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strRightButtonUp);
		}
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	dieLayer = Layer::create();
	addChild(dieLayer);
	dieLayer->setVisible(false);

	auto dieSprite = Sprite::create("die.png");
	dieSprite->setPosition(vSize.width/2,vSize.height/2+60);
	dieLayer->addChild(dieSprite);
	
	ui::Button* restart = ui::Button::create("continue.png");
	restart->setPosition(Vec2(vSize.width/2,vSize.height/2-60));
	restart->addClickEventListener([=](Ref* pSender){
		Hero::heroLife = 10;
		ShareData::getInstance()->heroScore = 0;
		ShareData::getInstance()->rankScore = 0;
		MainScene::level = 1;
		Director::getInstance()->replaceScene(MainScene::createScene());
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
	});
	dieLayer->addChild(restart);
}
void UICtrl::onExit(){
	_eventDispatcher->removeEventListener(listener);
	NotificationCenter::getInstance()->removeAllObservers(this);
	Layer::onExit();
}
void UICtrl::showLayer(){
	stopLayer->setVisible(true);
	playLayer->setVisible(false);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->pause();
}
void UICtrl::hideLayer(){
	stopLayer->setVisible(false);
	playLayer->setVisible(true);
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->resume();
}
void UICtrl::dieShow(cocos2d::Object* obj){
	stopLayer->setVisible(false);
	playLayer->setVisible(false);
	dieLayer->setVisible(true);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->pause();
}
void UICtrl::showBuff(Object* obj)
{
	moveButton->setSpriteFrame(SpriteFrame::create("moveButton.png", Rect(0,0,80,80)) );
}
void UICtrl::hideBuff(Object* obj)
{
	moveButton->setSpriteFrame(SpriteFrame::create("moveButton2.png", Rect(0,0,80,80)) );
}
