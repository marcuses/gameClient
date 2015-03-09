#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:

	static Bullet* create(TYPE type);
	bool init(TYPE type);
	void update(float dt);
	inline void setDir(Vec2 dir) { _dir = dir; }
	inline void setSpeed(float speed){ _speed = speed;}
	inline int getTime(){ return _time; }
	void addPhysics();
	void addAction();
private:
	Vec2 _dir;
	float _speed;
	int _time;
	TYPE _type;
};