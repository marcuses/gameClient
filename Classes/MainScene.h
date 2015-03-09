#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include "UICtrl.h"
#include "Hero.h"
#include "Bullet.h"
#include "MoveBody.h"
#include "Boss.h"
USING_NS_CC;

class MainScene :  public Layer  //test file
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	virtual void onEnter();
	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
	void update(float dt);

	bool onContactBegin(PhysicsContact& contact);
	void addBackGround(char *tmxName);
	void addListener();
	void addPhysics();
	void addObserver();
	//通过tilemap添加矩形
	Sprite* makeBox(ValueMap& dict, TYPE type,  const char* imgName, bool hasImg, float aDensity, float aRes, float aFriction); 
	//通过tilemap添加多边形
	Sprite* makePolygon(ValueMap& dict, TYPE type, const char* imgName, bool hasImg, bool dynamic, float aDensity, float aRes, float aFriction);
	void setViewPointCenter(Point position); 
	void heroShoot(Object * object);
	void enemyShoot(Object * object);
private:
	//Layer* _layer;
	TMXTiledMap* _tileMap;
	Hero* _hero;
	Boss* _boss;
	Vector<MoveBody*> _vMoveBody;
	Vector<Monster*> _vMonster;
	Vector<Bullet*> _vBullet;
	static Scene* _scene;
};


#endif // __MainScene_SCENE_H__
