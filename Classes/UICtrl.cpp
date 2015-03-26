#include "UICtrl.h"
#include "Headfile.h"
#include "LogInScene.h"
#include "MainScene.h"
#include "StartScene.h"
USING_NS_CC;

void UICtrl::onEnter(){
	Layer::onEnter();
	auto vSize = Director::getInstance()->getVisibleSize();

	//添加游戏逻辑按钮和暂停按钮和对应的响应函数
	playLayer = Layer::create();
	leftButton = Sprite::create("left.png");
	leftButton->setPosition(Vec2(50,leftButton->getContentSize().height));
	playLayer->addChild(leftButton);
	rightButton = Sprite::create("right.png");
	rightButton->setPosition(Vec2(120,rightButton->getContentSize().height));
	playLayer->addChild(rightButton);
	jumpButton = Sprite::create("jump.png");
	jumpButton->setPosition(Vec2(vSize.width-jumpButton->getContentSize().width,jumpButton->getContentSize().height));
	playLayer->addChild(jumpButton);
	fireButton = Sprite::create("fire.png");
	fireButton->setPosition(Vec2(jumpButton->getPositionX()-fireButton->getContentSize().width,fireButton->getContentSize().height));
	playLayer->addChild(fireButton);

	stopButton = Sprite::create("stop.png");
	stopButton->setPosition(vSize);
	stopButton->setAnchorPoint(Vec2(1.0f,1.0f));
	playLayer->addChild(stopButton);
	this->addChild(playLayer,1);
	//最好改成 EventListenerTouchAllAtOnce
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* e){
		if( stopButton->getBoundingBox().containsPoint(touch->getLocation())){
			showLayer();
		}else if( leftButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strLeftButtonDown);
		}else if( rightButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strRightButtonDown);
		}else if( jumpButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strJumpButtonDown);
		}else if( fireButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strHeroShoot);
		}
		return true;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* e)
	{
		if( leftButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strLeftButtonUp);
		}else if( rightButton->getBoundingBox().containsPoint(touch->getLocation())){
			NotificationCenter::getInstance()->postNotification(strRightButtonUp);
		}else if( jumpButton->getBoundingBox().containsPoint(touch->getLocation())){
			//NotificationCenter::getInstance()->postNotification(strJumpButtonUp);
		}
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	//暂停按钮按下后出现的控制层
	stopLayer = Layer::create();
	backButton = Sprite::create("UI/back.png");
	backButton->setPosition(Vec2(vSize.width/2-2*backButton->getContentSize().width,backButton->getContentSize().height));
	stopLayer->addChild(backButton);

	restartButton = Sprite::create("UI/restart.png");
	restartButton->setPosition(Vec2(vSize.width/2,backButton->getContentSize().height));
	stopLayer->addChild(restartButton);

	quitButton = Sprite::create("UI/quit.png");
	quitButton->setPosition(Vec2(vSize.width/2+2*quitButton->getContentSize().width,quitButton->getContentSize().height));
	stopLayer->addChild(quitButton);
	this->addChild(stopLayer,2);
	stopLayer->setVisible(false);
	auto listenerStop = EventListenerTouchOneByOne::create();		
	listenerStop->onTouchBegan = [=](Touch* touch, Event* e){
		if(	!stopLayer->isVisible() )	return false;
		if( backButton->getBoundingBox().containsPoint(touch->getLocation())){
			hideLayer();
		}else if( restartButton->getBoundingBox().containsPoint(touch->getLocation())){
			Hero::heroLife = 10;
			heroScore = 0;
			Director::getInstance()->replaceScene(MainScene::createScene());
			Director::getInstance()->resume();
		}else if( quitButton->getBoundingBox().containsPoint(touch->getLocation())){
			Director::getInstance()->replaceScene(StartScene::createScene());
			Director::getInstance()->resume();
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStop,stopLayer);
}
void UICtrl::onExit(){
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}
void UICtrl::showLayer(){
	stopLayer->setVisible(true);
	playLayer->setVisible(false);
	Director::getInstance()->pause();

}
void UICtrl::hideLayer(){
	stopLayer->setVisible(false);
	playLayer->setVisible(true);
	Director::getInstance()->resume();
}