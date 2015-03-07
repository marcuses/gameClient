#ifndef __STANDING_H__
#define __STANDING_H__
#include "cocos2d.h"

class Standing : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Standing);
};
#endif