#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:

	CREATE_FUNC(Bullet);
	bool init();
	void update(float dt);
	inline void setDir(Vec2 dir) { _dir = dir; }
	inline void setSpeed(float speed){ _speed = speed;}
	inline int getTime(){ return _time; }
	void addPhysics();
private:
	Vec2 _dir;
	float _speed;
	int _time;
};