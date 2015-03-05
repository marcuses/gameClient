#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class MoveBody : public Sprite
{
public:
	
	static MoveBody* create(const char* imgname,Sprite* sp, float speed, int type, float mFloor, float mCeil); //small表示下边界， big表示上边界, type表示移动平台的类型，1表示上移动，2表示左右移动,mFloor表示移动下界，mCeil表示移动上界
	bool init(const char* imgname,Sprite* sp, float speed, int type, float mFloor, float mCeil);  
	void update(float dt);
	inline void changeDir() { dir = -dir;}
private:
	float _floor,_ceil;
	float ox, oy;
	float _speed ;
	int _type; //type表示移动平台的类型，1表示上下，2表示左右
	Sprite* _sp;
	Vec2 dir;
};