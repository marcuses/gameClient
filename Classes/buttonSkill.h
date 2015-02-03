#include "cocos2d.h" 
USING_NS_CC;  
class SkillButton:public cocos2d::Layer{  
public:  
	
	static SkillButton* create(const char* fore_name,const char* back_name);  
	
	bool init(const char* fore_name,const char* back_name);  

	
	void BeginSkill();  
	
	void EndSkill();  
	
	bool IsSkilling;  

	
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);    
	
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);   


private:  
	Sprite *fore;    
	Sprite *back;    
	ProgressTimer *pt;
};
