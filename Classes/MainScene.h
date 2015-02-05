#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include "UICtrl.h"
#include "Hero.h"
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
	//通过tilemap添加矩形
	Sprite* makeBox(ValueMap& dict, TYPE type,  const char* imgName, bool hasImg); 
	//通过tilemap添加多边形
	Sprite* makePolygon(ValueMap& dict, TYPE type, const char* imgName, bool hasImg, bool dynamic);
	void setViewPointCenter(Point position);
	
private:
	Monster* _monster;
	//Layer* _layer;
	TMXTiledMap* _tileMap;
	Hero* _hero;
};


#endif // __MainScene_SCENE_H__
