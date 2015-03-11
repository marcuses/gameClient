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
	curLife = Label::createWithTTF(" x 3","fonts/Marker Felt.ttf",20);
	addChild(curLife);
	curLife->setPosition(50,lifeSprite->getPositionY());
	return true;
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