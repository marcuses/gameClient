#ifndef __AUTHOR_H__
#define __AUTHOR_H__
#include "cocos2d.h"

class Author : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Author);
};

#endif