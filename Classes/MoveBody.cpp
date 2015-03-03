#include "MoveBody.h"

MoveBody* MoveBody::create(const char* imgname,Sprite* sp,  float speed, int type){  

	MoveBody* ret = new MoveBody();  


	if(ret&&ret->init(imgname, sp, speed, type)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//°²È«É¾³ý  
	return nullptr;  
}  

bool MoveBody::init(const char* imgname, Sprite* sp, float speed, int type)  
{  
	if(!Sprite::initWithFile(imgname)) return false;
	this->setPhysicsBody(sp->getPhysicsBody());
	setTag(sp->getTag());
	setPosition(sp->getPosition());
	_speed = speed; 
	_type = type;
	if(type == 1) dir = Vec2(0, 1);
	else dir = Vec2(1, 0);
	return true;  
}  


void MoveBody::update(float dt)
{
	//setPosition(getPosition() + dir * _speed * dt);
	getPhysicsBody()->setVelocity( dir * _speed);
	/*if(_type == 1)
	{
	if(getPositionY() <= 3000)
	{
	setPositionY(3000);
	dir = -dir;
	}
	else if(getPositionY() >= 5000)
	{
	setPositionY(5000);
	dir = -dir;
	}
	}
	else
	{
	if(getPositionX() <= 3000)
	{
	setPositionX(3000);
	dir = -dir;
	}
	else if(getPositionX() >= 5000)
	{
	setPositionX(5000);
	dir = -dir;
	}
	}*/
	//if(_type == 1)
	//{
	//	getPhysicsBody()->setVelocity( dir * _speed);
	//	/*if(getPositionY() <= _floor)
	//	{
	//		setPositionY(_floor);
	//		dir = -dir;
	//	}
	//	else if(getPositionY() >= _ceil)
	//	{
	//		setPositionY(_ceil);
	//		dir = -dir;
	//	}*/
	//}
	//else
	//{
	//	getPhysicsBody()->setVelocity(dir * _speed );
	//	/*if(getPositionX() <= _floor)
	//	{
	//	setPositionX(_floor);
	//	dir = -dir;
	//	}
	//	else if(getPositionX() >= _ceil)
	//	{
	//	setPositionX(_ceil);
	//	dir = -dir;
	//	}*/
	//}
}