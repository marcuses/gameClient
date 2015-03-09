#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Bullet : public Sprite
{
public:

	static Bullet* create(TYPE type, Vec2 dir, float speed);
	bool init(TYPE type, Vec2 dir, float speed);
	void update(float dt);
	void addPhysics();
	void addAction();
	void del(float dt);
private:
	Vec2 _dir;
	float _speed;
	TYPE _type;
};