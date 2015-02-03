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
    
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    scene->addChild(layer);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -900));
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

//	auto brickNode1 = Node::create();
	auto brickNode2 = Node::create();

	auto brickBody = PhysicsBody::create();
	brickBody->addShape(PhysicsShapeBox::create(Size(20, 640)));
	brickBody->setDynamic(false);
	brickBody->setLinearDamping(0.0f);
	brickBody->setGravityEnable(false);
	brickBody->setCategoryBitmask(TYPE::BRICK);
	brickBody->setCollisionBitmask(TYPE::BRICK | TYPE::MONSTER | TYPE::HERO);
	brickBody->setContactTestBitmask(TYPE::BRICK | TYPE::MONSTER);
	//brickNode1->setPhysicsBody(brickBody);
	brickNode2->setPhysicsBody(brickBody);
	//brickNode1->setPosition(20, 320);
	brickNode2->setPosition(950, 320);
//	addChild(brickNode1, 1);
	addChild(brickNode2, 1);
//	brickNode1->setTag(TYPE::BRICK);
	brickNode2->setTag(TYPE::BRICK);
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	_monster = Monster::create();
	addChild(_monster, 1);
	_monster->setPosition(480, 320);
	scheduleUpdate();
    return true;
}
//
void HelloWorld::update(float dt)
{
	_monster->update(dt);
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