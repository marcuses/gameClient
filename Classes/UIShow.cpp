#include "UIShow.h"
#include "Headfile.h"
USING_NS_CC;
#include <string>
bool UIShow::init(){
	if(!Layer::init())	return false;
	Size vSize = Director::getInstance()->getVisibleSize();
	
	auto lifeSprite = Sprite::create("heroLife.png");
	addChild(lifeSprite);
	lifeSprite->setPosition(Vec2(120,600));

	curLife = Label::createWithTTF("10","fonts/Marker Felt.ttf",35);
	addChild(curLife);
	curLife->setPosition(lifeSprite->getPosition());

	auto heroScore = Sprite::create("heroScore.png");
	addChild(heroScore);
	heroScore->setPosition(Vec2(420,600));
	curScore = Label::createWithTTF("0","fonts/Marker Felt.ttf",35);
	addChild(curScore);
	curScore->setPosition(heroScore->getPosition());

	auto heroTime = Sprite::create("heroTime.png");
	addChild(heroTime);
	heroTime->setPosition(Vec2(720,600));

	curTime = Label::createWithTTF("0","fonts/Marker Felt.ttf",35);
	addChild(curTime);
	curTime->setPosition(heroTime->getPosition());
	
	runTime = 0;
	setCascadeOpacityEnabled(true);
	setOpacity(GLubyte(255*0.6));
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