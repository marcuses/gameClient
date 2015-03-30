#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "buttonSkill.h"
#include "Headfile.h"
#include "Gun.h"
#include <vector>
#include <string>
#include "Monster.h"
#include "WinScene.h"
#include "NextScene.h"
#include "cocostudio/CocoStudio.h"
#include "addJoint.h"
#include "Buff.h"
#include "dynamicTrap.h"
using namespace cocostudio;
using namespace std;
USING_NS_CC;
using namespace CocosDenshion;
int MainScene::level = 2;
int MainScene::hard = 1;
Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object

	auto _scene = Scene::createWithPhysics();
//	_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = MainScene::create();
	// add layer as a child to scene
	auto uiCtrl = UICtrl::create();
	_scene->addChild(uiCtrl,10);
	auto uiShow = UIShow::create();
	_scene->addChild(uiShow,9);
	auto uiKeyBoard = KeyBoardListener::create();
	_scene->addChild(uiKeyBoard,8);

	_scene->addChild(layer);
	_scene->getPhysicsWorld()->setGravity(Vec2(0, -900));
	// return the scene
	return _scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//_monster = Monster::create();
	//addChild(_monster, 1);
	//_monster->setPosition(200, 320);
	if(!Layer::init()) return false;
	//armature->getAnimation()->play("walk");
	//this->addChild(armature, 1);
	scheduleUpdate();
	schedule(schedule_selector(MainScene::updateMonster), 5.0);
	schedule(schedule_selector(MainScene::updateDynamicTrap), 0.3);
	m_nTeeterboardCnt = 0;
	m_nToneCnt = 0;

	return true;
}

void MainScene::onEnter()
{
	Layer::onEnter();

	/*ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation0.png","NewAnimation0.plist","NewAnimation.ExportJson");

	Armature *armature = Armature::create("NewAnimation");

	armature->setPosition(Point(5700, 320));*/
	char mpName[10];
	sprintf(mpName,"map%d.tmx", level);
	addBackGround(mpName);
	_hero = Hero::create();
	addChild(_hero, 3);

	_hero->setPosition(getTilePosition("heroPos", "heroPos"));
	_boss = Boss::create(level, hard);
	_boss->setPosition(getTilePosition("bossPos", "bossPos"));
	addChild(_boss, 2);
	_door = Sprite::create("door.png");
	_door->setPosition(getTilePosition("door", "door"));
	addChild(_door, 1);
	_door->setVisible(false);
	

	SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3",true);
	getScene()->getPhysicsWorld()->setAutoStep(false);
	addPhysics();
	addListener();
	addObserver();

	_trapId = 0;
	auto add = AddJoint::create();
	for (int nIndex = 0; nIndex < m_nTeeterboardCnt; nIndex++)
	{
		auto sp1 = getChildByTag(10000 + nIndex);
		add->addJoint(getScene(), sp1);
	}

	for (int nIndex = 0; nIndex < m_nToneCnt; nIndex++)
	{
		auto sp1 = getChildByTag(100000 + nIndex);
		add->addJoint(getScene(), sp1, sp1);
	}
	this->addChild(add);
}

void MainScene::onExit()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
	Layer::onExit();
}
void MainScene::update(float dt)
{
	//uiShow->setLife(_hero->getLife());
	nowTime += dt;
	setViewPointCenter(_hero->getPosition());
	for (int i = 0; i < 3; ++i)
	{
		getScene()->getPhysicsWorld()->step(1/180.0f);
	}
	if(_door->isVisible() && _door->getBoundingBox().containsPoint(_hero->getPosition()))
	{

		goNextLevel();
	}
}

void MainScene::addListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void MainScene::addObserver()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainScene::doorVisiable), strWin, NULL);
	//NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainScene::enemyShoot), strEnemyShoot, NULL);
}


void MainScene::updateDynamicTrap(float dt)
{
	Point pos = getTilePosition("dynamicTrap", "");
	_trapId = (_trapId + 1) % 10;
	auto objectTrap = _tileMap ->objectGroupNamed("dynamicTrap")->getObjects();
	for (auto& obj : objectTrap) //添加刺
	{
		auto dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		auto dyTrap = dynamicTrap::create();
		addChild(dyTrap, 2);
		dyTrap->setPosition(pos + Point(_trapId * 50, 0));
	}
}
void MainScene::doorVisiable(Object * object)
{
	_door->setVisible(true);
}
void MainScene::goNextLevel()
{
	unscheduleUpdate();
	level ++;
	rankScore += heroScore / int(nowTime+1);
	if(level > 3)
	{
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, WinScene::createScene()));
	}
	else
	{
		Director::getInstance()->replaceScene(TransitionMoveInR::create(1.0f, NextScene::createScene()));
	}
}
bool MainScene::onContactBegin(PhysicsContact& contact)
{
	//log("onContactBegin");
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if(spriteA == NULL || spriteB == NULL) return false;
//	log("%d %d",spriteA->getTag(), spriteB->getTag());
	if ((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::PLANK)
	{
		_hero = (Hero*)spriteA;
		_hero->setJump(false);
		return contact.getContactData()->normal.y < 0;
	}

	else if((spriteB && spriteB->getTag() == TYPE::HERO)
		&& spriteA && spriteA->getTag() == TYPE::PLANK)
	{
		_hero = (Hero*)spriteB;
		_hero->setJump(false);
		return contact.getContactData()->normal.y > 0;;
	}

	else if ((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::GROUND)
	{
		_hero = (Hero*)spriteA;
		_hero->setJump(false);
	}

	else if((spriteB && spriteB->getTag() == TYPE::HERO)
		&& spriteA && spriteA->getTag() == TYPE::GROUND)
	{
		_hero = (Hero*)spriteB;
		_hero->setJump(false);
	}

	else if ((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() >= 10000)
	{
		_hero = (Hero*)spriteA;
		_hero->setJump(false);
	}

	else if((spriteB && spriteB->getTag() == TYPE::HERO)
		&& spriteA && spriteA->getTag() >= 10000)
	{
		_hero = (Hero*)spriteB;
		_hero->setJump(false);
	}

	else if((spriteB && spriteB->getTag() == TYPE::MONSTER)
		&& spriteA && spriteA->getTag() == TYPE::BULLET)
	{
		auto monster = (Monster*)spriteB;
		auto bullet = (Bullet*)spriteA;
		monster->beHit(bullet->getPhysicsBody()->getVelocity());
		removeChild(bullet);
	}
	else if((spriteA && spriteA->getTag() == TYPE::MONSTER)
		&& spriteB && spriteB->getTag() == TYPE::BULLET)
	{
		auto monster = (Monster*)spriteA;
		auto bullet = (Bullet*)spriteB;
		monster->beHit(bullet->getPhysicsBody()->getVelocity());
		removeChild(bullet); 
	}
	else if((spriteA && spriteA->getTag() == TYPE::MONSTER)
		&& spriteB && spriteB->getTag() == TYPE::BRICK)
	{
		auto _monster = (Monster*)spriteA;
		_monster->changeDir();
	}
	else if((spriteB && spriteB->getTag() == TYPE::MONSTER)
		&& spriteA && spriteA->getTag() == TYPE::BRICK)
	{
		auto _monster = (Monster*)spriteB;
		_monster->changeDir();
	}
	else if((spriteA && spriteA->getTag() == TYPE::MONSTER)
		&& spriteB && spriteB->getTag() == TYPE::MONSTER)
	{
		((Monster*)spriteA)->changeDir();
		((Monster*)spriteB)->changeDir();
	}
	else if(spriteA && spriteA->getTag() == TYPE::TANGH)
	{
		auto phBody =  spriteB->getPhysicsBody();
		Vec2 v = phBody->getVelocity();
		phBody->setVelocity(Vec2(450, -v.y + 200));
	}
	else if(spriteB && spriteB->getTag() == TYPE::TANGH)
	{
		auto phBody =  spriteA->getPhysicsBody();
		Vec2 v = phBody->getVelocity();
		phBody->setVelocity(Vec2( 450, -v.y + 200));
	}
	else if((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::TRAP)
	{
		_hero = (Hero*)spriteA;
		_hero->beHit(Vec2(0,0));
	}
	else if((spriteA && spriteA->getTag() == TYPE::TRAP)
		&& spriteB && spriteB->getTag() == TYPE::HERO)
	{
		_hero = (Hero*)spriteB;
		_hero->beHit(Vec2(0,0));
	}
	else if((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::MONSTER)
	{
		_hero = (Hero*)spriteA;
		_hero->beHit(Vec2(0,0));
	}
	else if((spriteA && spriteA->getTag() == TYPE::MONSTER)
		&& spriteB && spriteB->getTag() == TYPE::HERO)
	{
		_hero = (Hero*)spriteB;
		_hero->beHit(Vec2(0,0));
	}
	else if((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::BOSS)
	{
		_hero = (Hero*)spriteA;
		_hero->beHit(Vec2(0,0));
	}
	else if((spriteA && spriteA->getTag() == TYPE::BOSS)
		&& spriteB && spriteB->getTag() == TYPE::HERO)
	{
		_hero = (Hero*)spriteB;
		_hero->beHit(Vec2(0,0));
	}
	else if((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::BULLETENEMY)
	{
		_hero = (Hero*)spriteA;
		_hero->beHit(spriteB->getPhysicsBody()->getVelocity());
		removeChild(spriteB);
	}
	else if((spriteA && spriteA->getTag() == TYPE::BULLETENEMY)
		&& spriteB && spriteB->getTag() == TYPE::HERO)
	{
		
		_hero = (Hero*)spriteB;
		_hero->beHit(spriteA->getPhysicsBody()->getVelocity());
		removeChild(spriteA);
	}
	else if((spriteA && spriteA->getTag() == TYPE::BULLET)
		&& spriteB && spriteB->getTag() == TYPE::BOSSWEAKNESS)
	{
		_boss->beHit(spriteA->getPhysicsBody()->getVelocity());
		removeChild(spriteA);
	}
	else if((spriteA && spriteA->getTag() == TYPE::BOSSWEAKNESS)
		&& spriteB && spriteB->getTag() == TYPE::BULLET)
	{
		_boss->beHit(spriteB->getPhysicsBody()->getVelocity());
		removeChild(spriteB);
	}

	else if ((spriteA && spriteA->getTag() == TYPE::HERO)
		&& spriteB && spriteB->getTag() == TYPE::BUFF)
	{
		_hero = (Hero*)spriteA;
		_hero->setBuff(true);
		removeChild(spriteB);
	}

	else if((spriteB && spriteB->getTag() == TYPE::HERO)
		&& spriteA && spriteA->getTag() == TYPE::BUFF)
	{
		_hero = (Hero*)spriteB;
		_hero->setBuff(true);
		removeChild(spriteA);
	}
	return true;
}
void MainScene::addBackGround(char *tmxName)
{
	String * csFilePath = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(tmxName));
	_tileMap = TMXTiledMap::createWithXML(csFilePath->getCString(),"");
	addChild(_tileMap, 0);
}

Sprite* MainScene::makeBox(ValueMap& dict, TYPE type, const char* imgName, bool hasImg, float aDensity, float aRes, float aFriction )
{
	auto mater = PhysicsMaterial(aDensity, aRes, aFriction);
	float x = dict["x"].asFloat();
	float y = dict["y"].asFloat();
	float width = dict["width"].asFloat();
	float height = dict["height"].asFloat();
	auto body = PhysicsBody::createBox(Size(width, height), mater);
	body->setCategoryBitmask(type);
	body->setCollisionBitmask(type | TYPE::MONSTER | TYPE::HERO | TYPE::BRICK | TYPE::GROUND | TYPE::BOSS | TYPE::TAI);
	body->setContactTestBitmask(type | TYPE::HERO | TYPE::MONSTER | TYPE::BRICK | TYPE::GROUND | TYPE::BOSS);
	body->setLinearDamping(0.0f);
	body->setDynamic(false);
	Sprite* sprite = nullptr;
	if(hasImg)
	{
		sprite = Sprite::create(imgName);
	}
	else
	{
		sprite = Sprite::create();
	}
	body->setPositionOffset(Point(width/2,height/2));
	sprite->setTag(type);
	sprite->setPosition(Point(x , y));
	sprite->setPhysicsBody(body);
	if (imgName == "banzi.png")
	{
		log("banszi");
		Size size = sprite->getContentSize();
		body->setPositionOffset(Point(0, 0));
		sprite->setPosition(Point(x + 10 , y ));
		body->setGravityEnable(true);
		body->setDynamic(true);
		sprite->setTag(10000 + m_nTeeterboardCnt);
		m_nTeeterboardCnt++;
	}
	else if (imgName == "tone.png")
	{
		Size size = sprite->getContentSize();
		body->setPositionOffset(Point(0, 0));
		sprite->setPosition(Point(x + size.width / 2, y - size.height / 2));
		body->setGravityEnable(true);
		body->setDynamic(true);

		sprite->setTag(100000 + m_nToneCnt++);
		
	}
	return sprite;
}

Sprite* MainScene::makePolygon(ValueMap& dict, TYPE type, const char* imgName, bool hasImg, bool dynamic, float aDensity, float aRes, float aFriction)
{
	auto mater = PhysicsMaterial(aDensity, aRes, aFriction);
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
		body->setCollisionBitmask(type | TYPE::MONSTER | TYPE::HERO | TYPE::BRICK | TYPE::GROUND | TYPE::TAI);
		body->setContactTestBitmask(type | TYPE::HERO | TYPE::MONSTER | TYPE::BRICK);
		body->setLinearDamping(0.0f);
		body->setDynamic(dynamic);
		Sprite* sprite = nullptr;
		if(hasImg)
			sprite = Sprite::create(imgName);
		else
			sprite = Sprite::create();
		sprite->setTag(type);
		if(imgName == "tai.png")
		{
			Size size = sprite->getContentSize();
			body->setPositionOffset(Point( -size.width / 2, size.height / 2));
			sprite->setPosition(Point(x + size.width / 2, y - size.height / 2));
			body->setGravityEnable(false);
		}
		else if(imgName == "BalanceBoard.png")
		{
			body->setPositionOffset(Point(-340, 0));
			sprite->setPosition(Point(x + 340, y ));
			body->setGravityEnable(false);
		}
		else if (imgName == "banzi.png")
		{
			log("banszi");
			Size size = sprite->getContentSize();
			body->setPositionOffset(Point(0, 0));
			sprite->setPosition(Point(x + 10 , y ));
			body->setGravityEnable(true);
			body->setDynamic(true);
			sprite->setTag(10000 + m_nTeeterboardCnt);
			m_nTeeterboardCnt++;
		}
		else
		{
			sprite->setPosition(Point(x , y));
		}
		sprite->setPhysicsBody(body);
	//	this->addChild(sprite);
		return sprite;
	}
	return nullptr;
}

Point MainScene::getTilePosition(std::string groupName, std::string objectName)
{
	auto dict = _tileMap->getObjectGroup(groupName)->getObject(objectName);
	float x = dict["x"].asFloat();
	float y = dict["y"].asFloat();
	return Point(x, y);
}
void MainScene::addPhysics()
{
	auto objectGroup0 = _tileMap ->objectGroupNamed("tai")->getObjects();
	for (auto& obj : objectGroup0) //添加跷跷板
	{
		ValueMap& dict = obj.asValueMap();
		auto sprite = makeBox(dict, TYPE::GROUND, "banzi.png", true, 10, 0, 1);
		this->addChild(sprite);
	}
	/*
	auto objectGroup0 = _tileMap ->objectGroupNamed("taitai")->getObjects();
	for (auto& obj : objectGroup0) //添加跷跷板
	{
		ValueMap& dict = obj.asValueMap();
		auto sprite = makeBox(dict, TYPE::GROUND, "banzi.png", true, 10, 0, 1);
		this->addChild(sprite);
	}
	*/
	auto objectGroup00 = _tileMap ->objectGroupNamed("tone")->getObjects();
	for (auto& obj : objectGroup00) //添加石头
	{
		ValueMap& dict = obj.asValueMap();
		auto sprite = makeBox(dict, TYPE::GROUND, "tone.png", true, 10, 0, 10);
		this->addChild(sprite);
	}

	auto objectGroup = _tileMap ->objectGroupNamed("ObjectsBox")->getObjects();
	for (auto& obj : objectGroup) //添加矩形地面
	{
		ValueMap& dict = obj.asValueMap();
		auto sprite = makeBox(dict, TYPE::GROUND, "", false, 100, 0, 1);
		addChild(sprite);
	}

	auto objectGroup1 = _tileMap ->objectGroupNamed("ObjectsPolygon")->getObjects();
	for (auto& obj : objectGroup1)  //添加多边形地面
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::GROUND, "", false, false, 100, 0, 1);
		addChild(sprite);
	}

	auto objectPlank = _tileMap ->objectGroupNamed("Plank")->getObjects();
	for (auto& obj : objectPlank)  //添加木板
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::PLANK, "", false, false, 100, 0, 1);
		addChild(sprite);
	}
	if(MainScene :: level <= 1)
	{
		auto objectGroup2 = _tileMap ->objectGroupNamed("ObjectsTanhuang")->getObjects();
		for (auto& obj : objectGroup2) //添加弹簧
		{
			auto dic= obj.asValueMap();
			auto sprite = makePolygon(dic, TYPE::TANGH, "", false, false,100, 0, 1);
			addChild(sprite);
		}
	}

	//添加移动台水平
	auto objectsHmove = _tileMap ->objectGroupNamed("hMove")->getObjects();
	for (auto& obj : objectsHmove)
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::PLANK, "tai.png", true, true, 0, 0, 1);
		Size sz = sprite->getContentSize();
		Point pos = sprite->getPosition();
		auto moveBody = MoveBody::create("tai.png", sprite, 100, 2,pos.x - sz.width, pos.x );
		addChild(moveBody);
	}


	//添加移动台上下
	auto objectsVmove = _tileMap ->objectGroupNamed("ObjectsSwing")->getObjects();
	for(auto& obj : objectsVmove)
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::PLANK, "BalanceBoard.png", true, true, 0, 0, 1);
		Size sz = sprite->getContentSize();
		Point pos = sprite->getPosition();
		auto moveBody = MoveBody::create("BalanceBoard.png", sprite, 100, 1,pos.y  , pos.y + 200);
		addChild(moveBody);
	}
	auto objectGroupEnemy = _tileMap ->objectGroupNamed("Enemy")->getObjects();
	for (auto& obj : objectGroupEnemy) //添加小怪
	{
		auto dic= obj.asValueMap();
		float x = dic["x"].asFloat();
		float y = dic["y"].asFloat();
		auto ememy = Monster::create(hard,rand() % 4);
		ememy->setPosition(x, y);
		addChild(ememy);
	}


	auto objectGroupsEnemy = _tileMap ->objectGroupNamed("sEnemy")->getObjects();
	for (auto& obj : objectGroupsEnemy) //添加炮台
	{
		auto dic= obj.asValueMap();
		float x = dic["x"].asFloat();
		float y = dic["y"].asFloat();
		auto ememy = Gun::create(hard);
		ememy->setPosition(x, y);
		addChild(ememy);
	}

	auto objectGroupTrap = _tileMap ->objectGroupNamed("trap")->getObjects();
	for (auto& obj : objectGroupTrap) //添加陷阱
	{
		auto dic= obj.asValueMap();
		auto sprite = makePolygon(dic, TYPE::TRAP, "", false,false,0, 0, 0);
		sprite->getPhysicsBody()->setCollisionBitmask(0xff);
		sprite->getPhysicsBody()->setContactTestBitmask(0xff);
		addChild(sprite);

	}

	auto objectGroupBrick = _tileMap ->objectGroupNamed("Brick")->getObjects();
	for (auto& obj : objectGroupBrick) //添加反弹物
	{
		auto dic= obj.asValueMap();
		auto sprite = makeBox(dic, TYPE::BRICK, "", false,100, 0, 1);
		sprite->getPhysicsBody()->setCollisionBitmask(TYPE :: MONSTER | TYPE:: BRICK);
		sprite->getPhysicsBody()->setContactTestBitmask(TYPE :: MONSTER | TYPE:: BRICK);
		addChild(sprite);

	}

	auto objectMonsterPoint = _tileMap ->objectGroupNamed("monsterPoint")->getObjects();
	for (auto& obj : objectMonsterPoint) //添加出怪点
	{
		auto dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		auto mPoint = Armature::create("monsterPoint");
		mPoint->setPosition(Point(x,y));
		mPoint->getAnimation()->play("run");
		addChild(mPoint, 2); 
	}

	auto objectBuff = _tileMap ->objectGroupNamed("buff")->getObjects();
	for (auto& obj : objectBuff) //添加buff点
	{
		auto dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		auto buff = Buff::create();
		buff->setPosition(Point(x,y));
		addChild(buff, 2); 
	}

}

void MainScene::updateMonster(float dt)
{
	auto objectMonsterPoint = _tileMap ->objectGroupNamed("monsterPoint")->getObjects();
	for (auto& obj : objectMonsterPoint) //出怪
	{
		auto dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		if(fabs(x - _hero->getPositionX()) > 960) continue;
		auto ememy = Monster::create(hard,rand() % 4);
		ememy->setPosition(Point(x,y));
		addChild(ememy);
	}
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
