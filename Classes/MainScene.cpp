#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "buttonSkill.h"
#include "Headfile.h"

#include <vector>
#include <string>
#include "Monster.h"
using namespace std;
USING_NS_CC;
using namespace CocosDenshion;
Scene* MainScene::_scene = nullptr;
Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	_scene = Scene::createWithPhysics();

	_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	// 'layer' is an autorelease object
	auto layer = MainScene::create();
	// add layer as a child to scene
	_scene->addChild(layer);
	_scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

	auto uiCtrl = UICtrl::create();
	_scene->addChild(uiCtrl,10);

	// return the scene
	return _scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	_monster = Monster::create();
	//addChild(_monster, 1);
	//_monster->setPosition(200, 320);
	_hero = Hero::create();
	addChild(_hero, 1);
	_hero->setPosition(4500, 320);
	
	scheduleUpdate();
	return true;
}

void MainScene::onEnter()
{
	Layer::onEnter();
	auto size = Director::getInstance()->getWinSize();
	addBackGround("map.tmx");
	addPhysics();
	addListener();
	 _scene->getPhysicsWorld()->setAutoStep(false);
}

void MainScene::update(float dt)
{
	_monster->update(dt);
	_hero->update(dt);
	setViewPointCenter(_hero->getPosition());
	_moveBody->update(dt);
	for (int i = 0; i < 3; ++i)
	{
		_scene->getPhysicsWorld()->step(1/180.0f);
	}
}

void MainScene::addListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool MainScene::onContactBegin(PhysicsContact& contact)
{
	log("onContactBegin");
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();				
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();	
	log("%d %d",spriteA->getTag(), spriteB->getTag());
	if ((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::GROUND)
	{
		_hero = (Hero*)spriteA;
		_hero->setJump(false);
		return contact.getContactData()->normal.y < 0;
	}

	else if((spriteB && spriteB->getTag() == TYPE::HERO)
		&& spriteA && spriteA->getTag() == TYPE::GROUND)
	{
		_hero = (Hero*)spriteB;
		_hero->setJump(false);
		return contact.getContactData()->normal.y > 0;;
	}

	else if((spriteA && spriteA->getTag() == TYPE::MONSTER)
		&& spriteB && spriteB->getTag() == TYPE::BRICK)
	{
		_monster = (Monster*)spriteA;
		_monster->changeDir();
	}
	else if((spriteB && spriteB->getTag() == TYPE::MONSTER)
		&& spriteA && spriteA->getTag() == TYPE::BRICK)
	{
		_monster = (Monster*)spriteB;
		_monster->changeDir();
	}
	else if((spriteA && spriteA->getTag() == TYPE::GROUND)
		&& spriteB && spriteB->getTag() == TYPE::BRICK)
	{
		_moveBody = (MoveBody*)spriteA;
		_moveBody->changeDir();
	}
	else if((spriteB && spriteB->getTag() == TYPE::GROUND)
		&& spriteA && spriteA->getTag() == TYPE::BRICK)
	{
		_moveBody = (MoveBody*)spriteB;
		_moveBody->changeDir();
	}
	else if(spriteA && spriteA->getTag() == TYPE::TANGH)
	{
		auto phBody =  spriteB->getPhysicsBody();
		Vec2 v = phBody->getVelocity();
		phBody->setVelocity(Vec2(v.x + 50, -v.y + 200));
	}
	else if(spriteB && spriteB->getTag() == TYPE::TANGH)
	{
		auto phBody =  spriteA->getPhysicsBody();
		Vec2 v = phBody->getVelocity();
		phBody->setVelocity(Vec2(v.x + 50, -v.y + 200));
	}
	return true;
}
void MainScene::addBackGround(char *tmxName)
{
	String * csFilePath = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(tmxName));
	_tileMap = TMXTiledMap::createWithXML(csFilePath->getCString(),"");
	addChild(_tileMap, 0);
}

Sprite* MainScene::makeBox(ValueMap& dict, TYPE type, const char* imgName, bool hasImg )
{
	auto mater = PhysicsMaterial(100.0f, 0.0f, 1.0f);
	float x = dict["x"].asFloat();
	float y = dict["y"].asFloat();
	float width = dict["width"].asFloat();
	float height = dict["height"].asFloat();
	auto body = PhysicsBody::createBox(Size(width, height), mater);
	body->setCategoryBitmask(type);
	body->setCollisionBitmask(type | TYPE::MONSTER | TYPE::HERO | TYPE::BRICK | TYPE::GROUND);
	body->setContactTestBitmask(type | TYPE::HERO | TYPE::MONSTER | TYPE::BRICK | TYPE::GROUND);
	body->setLinearDamping(0.0f);
	body->setDynamic(false);
	Sprite* sprite = nullptr;
	if(hasImg)
		sprite = Sprite::create(imgName);
	else
		sprite = Sprite::create();
	body->setPositionOffset(Point(width/2,height/2));
	sprite->setTag(type);
	sprite->setPosition(Point(x , y));
	sprite->setPhysicsBody(body);
	//this->addChild(sprite);
	return sprite;
}

Sprite* MainScene::makePolygon(ValueMap& dict, TYPE type, const char* imgName, bool hasImg, bool dynamic)
{
	auto mater = PhysicsMaterial(100.0f, 0.0f, 1.0f);
	float x = dict.at("x").asFloat();
	float y = dict.at("y").asFloat();
	auto pointsVector = dict.at("points").asValueVector();
	auto size = pointsVector.size();
	//获取点
	if (size>0)
	{
		Vec2* points= new Vec2[size];
		int cnt =0 ;
		for (auto pointValue:pointsVector)
		{
			auto dicp = pointValue.asValueMap();
			auto x  = dicp.at("x").asFloat();
			auto y  = -dicp.at("y").asFloat();//y取负值
			points[cnt]= Vec2( x , y );
			cnt++;
		}
		//绘制折线
		auto body = PhysicsBody::createEdgePolygon(points, cnt, mater);
		body->setCategoryBitmask(type);
		body->setCollisionBitmask(type | TYPE::MONSTER | TYPE::HERO | TYPE::BRICK);
		body->setContactTestBitmask(type | TYPE::HERO | TYPE::MONSTER | TYPE::BRICK);
		body->setLinearDamping(0.0f);

		body->setDynamic(dynamic);
		Sprite* sprite = nullptr;
		if(hasImg)
			sprite = Sprite::create(imgName);
		else
			sprite = Sprite::create();
		sprite->setTag(type);
		if(imgName == "Swing.png")
		{
			body->setPositionOffset(Point( -115, 75));
			sprite->setPosition(Point(x + 115, y - 75));
			body->setGravityEnable(false);
		}
		else
			sprite->setPosition(Point(x , y));
		sprite->setPhysicsBody(body);
	//	this->addChild(sprite);
		return sprite;
	}
	return nullptr;
}
void MainScene::addPhysics()
{
	auto objectGroup = _tileMap ->objectGroupNamed("ObjectsBox")->getObjects();
	for (auto& obj : objectGroup) //添加矩形地面
	{
		ValueMap& dict = obj.asValueMap();
		auto sprite = makeBox(dict, TYPE::GROUND, "", false);
		addChild(sprite);
	}

	auto objectGroup1 = _tileMap ->objectGroupNamed("ObjectsPolygon")->getObjects();
	for (auto& obj : objectGroup1)  //添加多边形地面
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::GROUND, "", false, false);
		addChild(sprite);
	}

	
	auto objectGroup2 = _tileMap ->objectGroupNamed("ObjectsTanhuang")->getObjects();
	for (auto& obj : objectGroup2) //添加弹簧
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::TANGH, "", false, false);
		addChild(sprite);
	}

	//添加秋千
	auto objects = _tileMap ->objectGroupNamed("ObjectsSwing");
	auto B1 = objects->getObject("b1");
	auto B2 = objects->getObject("b2");
	auto Swing = objects->getObject("Swing");
	char name[100];
	for(int i = 1;i <= 2; i++)
	{
		sprintf(name, "b%d", i);
		auto vMap = objects->getObject(name);
		auto sp = makeBox(vMap, TYPE::BRICK, "", false);
		sp->getPhysicsBody()->setCollisionBitmask(0xff);
		sp->getPhysicsBody()->setContactTestBitmask(0xff);
		sp->getPhysicsBody()->setCategoryBitmask(0xff);
		sp->setTag(TYPE::BRICK);
		addChild(sp);
	}
	
	auto spw = makePolygon(Swing, TYPE::GROUND, "Swing.png", true, true);
	_moveBody = MoveBody::create("Swing.png", spw, 100, 2);
	_moveBody->getPhysicsBody()->setCollisionBitmask(0xff);
	_moveBody->getPhysicsBody()->setContactTestBitmask(0xff);
	_moveBody->getPhysicsBody()->setCategoryBitmask(0xff);
	addChild(_moveBody);
}


void MainScene::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	//CCLOG("viewP = %f %f", viewPoint.x, viewPoint.y);

	this->setPosition(viewPoint);
}