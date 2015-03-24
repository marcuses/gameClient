#include "UIShow.h"
#include "Headfile.h"
USING_NS_CC;
#include <string>
bool UIShow::init(){
	if(!Layer::init())	return false;
	Size vSize = Director::getInstance()->getVisibleSize();
	lifeSprite = Sprite::create("UI/life.png");
	addChild(lifeSprite);
	lifeSprite->setPosition(20,vSize.height-lifeSprite->getContentSize().height);

	//其实3是有问题的0.0
	curLife = Label::createWithTTF(" x 10","fonts/Marker Felt.ttf",20);
	addChild(curLife);
	curLife->setPosition(50,lifeSprite->getPositionY());
	
	runTime = 0;
	curTime = Label::createWithTTF("0","fonts/Marker Felt.ttf",30);
	addChild(curTime);
	curTime->setPosition(vSize.width/2,vSize.height-curTime->getContentSize().width);
	
	scheduleUpdate();

	return true;
}
void UIShow::update(float dt){
	runTime += dt;
	char tmp[10];
	sprintf(tmp,"%.1f",runTime);
	curTime->setString(tmp);
}
void UIShow::onEnter(){
	Layer::onEnter();
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(UIShow::setLife), showHeroLife, NULL);
}
void UIShow::onExit(){
	NotificationCenter::getInstance()->removeObserver(this,showHeroLife);
	Layer::onExit();
}
void UIShow::setLife(Object* object){
	String* life = (String*)(object);
	curLife->setString(life->_string);
}
float UIShow::getTime(){
	return runTime;
}