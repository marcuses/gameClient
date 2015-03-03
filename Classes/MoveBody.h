#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class MoveBody : public Sprite
{
public:
	
	static MoveBody* create(const char* imgname,Sprite* sp, float speed, int type); //small表示下边界， big表示上边界, type表示移动平台的类型，1表示上下，2表示左右
	bool init(const char* imgname,Sprite* sp, float speed, int type);  
	void update(float dt);
	void changeDir()
	{
		dir = -dir;
	}
private:
	
	float _speed ;
	int _type; //type表示移动平台的类型，1表示上下，2表示左右
	Sprite* _sp;
	Vec2 dir;
};