#pragma once
#include "cocos2d.h"
USING_NS_CC;
class AddJoint  : public Node 
{
public:
	AddJoint(void);
	~AddJoint(void);

	static AddJoint* create();
	bool init();  

public:
	bool addJoint(Scene* _scene, Node* sp1);
	bool addJoint(Scene* _scene, Node* sp1, Node* sp2);
};

