#include "Splash.h"
#include "LogInScene.h"
USING_NS_CC;

Scene* Splash::createScene(){
    auto scene = Scene::create();
    
    auto layer = Splash::create();

    scene->addChild(layer);

    return scene;
}

bool Splash::init(){
    if(!Layer::init())	 return false;
	auto sprite = Sprite::create("Splash.png");
	addChild(sprite);
	sprite->ignoreAnchorPointForPosition(true);
	scheduleOnce(schedule_selector(Splash::updateOnce), 1.2f);
    return true;
}

void Splash::updateOnce(float dt){
	auto scene = LogInScene::createScene();
	//auto sceneTrasition = TransitionJumpZoom::create(0.3f,scene);
	auto sceneTrasition = TransitionFade::create(0.3f,scene);
	Director::getInstance()->replaceScene(sceneTrasition);
}