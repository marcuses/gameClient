#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include "UICtrl.h"
USING_NS_CC;
class HelloWorld :  public Layer  //test file
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
  
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void update(float dt);
	bool onContactBegin(PhysicsContact& contact);

	void addBackGround(char *tmxName);

	void addPhysics();
	void setViewPointCenter(Point position);
private:
	Monster* _monster;
	Layer* _layer;
	TMXTiledMap* _tileMap;
};


#endif // __HELLOWORLD_SCENE_H__
