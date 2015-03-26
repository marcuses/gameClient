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

	curScore = Label::createWithTTF("0","fonts/Marker Felt.ttf",30);
	addChild(curScore);
	curScore->setPosition(2*vSize.width/3,vSize.height-curScore->getContentSize().height/2);
	
	runTime = 0;
	curTime = Label::createWithTTF("0","fonts/Marker Felt.ttf",30);
	addChild(curTime);
	curTime->setPosition(vSize.width/3,vSize.height-curTime->getContentSize().height/2);
	
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
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(UIShow::setScore), showScore, NULL);
}
void UIShow::onExit(){
	NotificationCenter::getInstance()->removeObserver(this,showHeroLife);
	NotificationCenter::getInstance()->removeObserver(this,showScore);
	Layer::onExit();
}
void UIShow::setLife(Object* object){
	String* life = (String*)(object);
	curLife->setString(life->_string);
}
void UIShow::setScore(cocos2d::Object* object){
	String* score = (String*)(object);
	curScore->setString(score->_string);
}
float UIShow::getTime(){
	return runTime;
}                                                                                            