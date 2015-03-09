#include "MoveBody.h"

MoveBody* MoveBody::create(const char* imgname,Sprite* sp,  float speed, int type, float mFloor, float mCeil){  

	MoveBody* ret = new MoveBody();  


	if(ret&&ret->init(imgname, sp, speed, type, mFloor, mCeil)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  

bool MoveBody::init(const char* imgname, Sprite* sp, float speed, int type, float mFloor, float mCeil)  
{  
	if(!Sprite::initWithFile(imgname)) return false;
	this->setPhysicsBody(sp->getPhysicsBody());
	getPhysicsBody()->setGravityEnable(false);
	_floor = mFloor;
	_ceil = mCeil;
	setTag(sp->getTag());
	setPosition(sp->getPosition());
	ox = getPositionX();
	oy = getPositionY();
	_speed = speed; 
	_type = type;
	if(type == 1) dir = Vec2(0, 1);
	else dir = Vec2(1, 0);
	scheduleUpdate();
	return true;  
}  


void MoveBody::update(float dt)
{
	//setPosition(getPosition() + dir * _speed * dt);
	getPhysicsBody()->setVelocity( dir * _speed);
	if(_type == 1)
	{
		setPositionX(ox);
		if(getPositionY() <= _floor)
		{
			setPositionY(_floor + 10);
			dir = -dir;
		}
		else if(getPositionY() >= _ceil)
		{
			setPositionY(_ceil - 10);
			dir = -dir;
		}
	}
	else
	{
		setPositionY(oy);
		if(getPositionX() <= _floor)
		{
			setPositionX(_floor + 10);
			dir = -dir;
		}
		else if(getPositionX() >= _ceil)
		{
			CCLOG("%f", getPositionX());
			setPositionX(_ceil - 10);
			dir = -dir;
		}
	}
}