#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:
	static Bullet* create(TYPE type, Vec2 dir, float speed, int bType);
	bool init(TYPE type, Vec2 dir, float speed, int bType);
	void update(float dt);
	void addPhysics();
	void addAction();
	void del();
private:
	Vec2 _dir;
	float _speed;
	TYPE _type;
	int _bType;
	float _maxTime;
	float _nowTime;
};