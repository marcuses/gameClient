#include "UICtrl.h"
USING_NS_CC;

bool UICtrl::init(){
	if(!Layer::init())	return false;
	auto vSize = Director::getInstance()->getVisibleSize();
	stop = Sprite::create("UI/stop.png");
	stop->setPosition(vSize);
	stop->setAnchorPoint(Vec2(1.0f,1.0f));
	this->addChild(stop,0);
	
	_myCtrlLayer = Layer::create();
	back = Sprite::create("UI/back.png");
	back->setPosition(2*vSize.width/5,vSize.height/4);
	_myCtrlLayer->addChild(back);

	quit = Sprite::create("UI/quit.png");
	quit->setPosition(3*vSize.width/5,vSize.height/4);
	_myCtrlLayer->addChild(quit);
	this->addChild(_myCtrlLayer,1);
	_myCtrlLayer->setVisible(false);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* e){
		if( stop->getBoundingBox().containsPoint(touch->getLocation())){
			showLayer();
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [=](Touch* touch, Event* e){
		if(	!_myCtrlLayer->isVisible() )	return false;
		if( back->getBoundingBox().containsPoint(touch->getLocation())){
			hideLayer();
		}else if( quit->getBoundingBox().containsPoint(touch->getLocation())){
			Director::getInstance()->end();
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,_myCtrlLayer);

	return true;
}

void UICtrl::showLayer(){
	_myCtrlLayer->setVisible(true);
	Director::getInstance()->pause();

}
void UICtrl::hideLayer(){
	_myCtrlLayer->setVisible(false);
	Director::getInstance()->resume();
}