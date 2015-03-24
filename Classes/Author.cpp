#include "Author.h"
#include "StartScene.h"
USING_NS_CC;

Scene* Author::createScene(){
	auto scene = Scene::create();

	auto layer = Author::create();

	scene->addChild(layer);

	return scene;
}
bool Author::init(){
	if(!Layer::init())	return false;
	auto bgSprite = Sprite::create("MainMenu.png");
	bgSprite->ignoreAnchorPointForPosition(true);
	addChild(bgSprite);

	auto authorLabel	= Label::createWithTTF("Author", "fonts/Marker Felt.ttf", 50);
	authorLabel->setPosition(180,540);
	addChild(authorLabel);

	auto nameLabel	= Label::createWithTTF("DreamYard", "fonts/Marker Felt.ttf", 50);
	nameLabel->setPosition(180,240);
	addChild(nameLabel);

	auto backMenu = MenuItemImage::create("back.png","back.png",[](Ref* pSender){
		auto scene	= StartScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	backMenu->setPosition(0,0);
	backMenu->ignoreAnchorPointForPosition(true);
	auto menu = Menu::create(backMenu,NULL);
	addChild(menu);
	menu->setPosition(0,0);
	return true;
}