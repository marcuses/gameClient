#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "buttonSkill.h"
#include "Headfile.h"
#include <vector>
#include <string>
#include "Monster.h"
using namespace std;
USING_NS_CC;
using namespace CocosDenshion;



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

	auto uiCtrl = UICtrl::create();
	scene->addChild(uiCtrl,10);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	vector<string> searchPath; 
	searchPath.push_back("StartScene"); 
	searchPath.push_back("Role"); 
	searchPath.push_back("GameOver");
	searchPath.push_back("WinScene");
	searchPath.push_back("NextScene");
	searchPath.push_back("Map");
	CCFileUtils::getInstance()->setSearchPaths(searchPath); 
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//this->getPhysicsWorld()->setGravity(Vec2(0, -900));
	auto size = Director::getInstance()->getWinSize();
	/*auto btn_skill=SkillButton::create("skill_fore.png","skill_back.png");  
	btn_skill->setPosition(Vec2(size.width-150,60));  
	this->addChild(btn_skill,2);*/

	auto groundNode = Node::create();
	float landHeight = 117.0f;
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(960, landHeight)));
	groundBody->setDynamic(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setGravityEnable(false);
	groundBody->setCategoryBitmask(TYPE::BRICK);
	groundBody->setCollisionBitmask(TYPE::BRICK | TYPE::MONSTER | TYPE::HERO);
	//groundBody->setContactTestBitmask(0x01);
	groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(480, landHeight/2);
	groundNode->setTag(TYPE::BRICK);
	addChild(groundNode);

	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	_monster = Monster::create();
	addChild(_monster, 1);
	_monster->setPosition(800, 320);

	addBackGround("map.tmx");
	addPhysics();
	scheduleUpdate();
    return true;
}
//
void HelloWorld::update(float dt)
{
	_monster->update(dt);
	setViewPointCenter(_monster->getPosition());
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();				
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();				
	if (spriteA && spriteA->getTag() == TYPE::MONSTER)
	{
		_monster = (Monster*)spriteA;
		_monster->changeDir();
	}

	else if(spriteB && spriteB->getTag() == TYPE::MONSTER)
	{
		_monster = (Monster*)spriteB;
		_monster->changeDir();
	}

	log("onContactBegin");
	return true;
}

void HelloWorld::addBackGround(char *tmxName)
{
	String * csFilePath = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(tmxName));
	_tileMap = TMXTiledMap::createWithXML(csFilePath->getCString(),"");
	addChild(_tileMap, 0);
}

void HelloWorld::addPhysics()
{
	auto objectGroup = _tileMap ->objectGroupNamed("Objects")->getObjects();
	for (auto& obj : objectGroup) 
	{
		ValueMap& dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		auto body = PhysicsBody::createBox(Size(width, height), PHYSICSBODY_MATERIAL_DEFAULT);
		body->setCategoryBitmask(TYPE::BRICK);
		body->setCollisionBitmask(TYPE::BRICK | TYPE::MONSTER | TYPE::HERO);
		//body->setContactTestBitmask(3);
		body->setLinearDamping(0.0f);
		body->setDynamic(false);
		Sprite* sprite;
		sprite = Sprite::create();
		body->setPositionOffset(Point(width/2,height/2));
		sprite->setPosition(Point(x , y));
		sprite->setPhysicsBody(body);
		this->addChild(sprite);
	}
}

void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	CCLOG("viewP = %f %f", viewPoint.x, viewPoint.y);

	this->setPosition(viewPoint);
	//timeLabel->setPosition(actualPosition.x, actualPosition.y + winSize.height / 2 - 50);
}