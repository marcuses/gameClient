#include "UICtrl.h"
#include "Headfile.h"
USING_NS_CC;

bool UICtrl::init(){
	if(!Layer::init())	return false;
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
	auto listener = EventListenerTouchOneByOne::create();
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
	backButton->setPosition(Vec2(vSize.width/2-backButton->getContentSize().width,backButton->getContentSize().height));
	stopLayer->addChild(backButton);
	quitButton = Sprite::create("UI/quit.png");
	quitButton->setPosition(Vec2(vSize.width/2+quitButton->getContentSize().width,quitButton->getContentSize().height));
	stopLayer->addChild(quitButton);
	this->addChild(stopLayer,2);
	stopLayer->setVisible(false);			//初始不可见

	auto listenerStop = EventListenerTouchOneByOne::create();		
	listenerStop->onTouchBegan = [=](Touch* touch, Event* e){
		if(	!stopLayer->isVisible() )	return false;
		if( backButton->getBoundingBox().containsPoint(touch->getLocation())){
			hideLayer();
		}else if( quitButton->getBoundingBox().containsPoint(touch->getLocation())){
			Director::getInstance()->end();
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerStop,stopLayer);

	return true;
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