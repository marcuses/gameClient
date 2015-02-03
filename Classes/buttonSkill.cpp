#include "buttonSkill.h"  
SkillButton* SkillButton::create(const char* fore_name,const char* back_name){  

	SkillButton* ret = new SkillButton();  

	
	if(ret&&ret->init(fore_name,back_name)){  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret);//安全删除  
	return nullptr;  
}  
bool SkillButton::init(const char* fore_name,const char* back_name)  
{  
	if(!CCLayer::init()){  
		return false;  
	}  

	this->setTouchEnabled(true);//开启触摸  
	fore=CCSprite::create(fore_name);//fore_name是较亮的图片   
	this->addChild(fore,1);    

	back=CCSprite::create(back_name);//back_name是较暗的图片    
	pt=CCProgressTimer::create(back);  
	this->addChild(pt,2);    
	IsSkilling = false;

	auto _listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(SkillButton::onTouchBegan,this);
	_listener_touch->onTouchEnded = CC_CALLBACK_2(SkillButton::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);//true表示只有当前层能截取到触摸事件
	return true;  
}  
//开始冷却技能  
void SkillButton::BeginSkill()  
{  
	//pt->stopAllActions();
	//转圈的CD实现    
	pt->setType(cocos2d::ProgressTimerType(kCCProgressTimerTypeRadial));   
	ProgressTo *waittime=ProgressTo::create(2,100);  
	//创建回调动作，技能冷却结束后调用EndSkill()  
	CallFunc* callFunc=CallFunc::create(this,callfunc_selector(SkillButton::EndSkill));  
	//创建连续动作  
	ActionInterval* act=Sequence::create(waittime,callFunc,NULL);  
	pt->setVisible(true);  
	IsSkilling=true;  
	pt->runAction(act);    

}  
//冷却技能结束后  
void SkillButton::EndSkill()  
{  
	pt->setVisible(false);  
	pt->stopAllActions();
	IsSkilling=false;  

	CCNotificationCenter::sharedNotificationCenter()->postNotification("jian_xue");  
}  

//判断是否点击的范围为精灵 如果是则执行动作    
void SkillButton::onTouchEnded(Touch *pTouch, Event *pEvent)    
{    
	if(IsSkilling)  
		return;  
	//判断是否点击在精灵上面  
	CCPoint touchPoint = convertTouchToNodeSpace(pTouch);    
	if(fore->boundingBox().containsPoint(touchPoint))    
	{    

		BeginSkill();  
	}    
}    

//返回true表示支持触摸 返回false表示忽略     
bool SkillButton::onTouchBegan(Touch *pTouch, Event *pEvent)    
{    
	return true;    
}   
///注册触摸代理支持,其中第二个参数为触摸的响应等级 值越小 响应等级越高    
