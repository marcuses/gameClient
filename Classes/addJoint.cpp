#include "addJoint.h"


AddJoint::AddJoint(void)
{
}


AddJoint::~AddJoint(void)
{
}

AddJoint* AddJoint::create()
{
	AddJoint* ret = new AddJoint();  


	if(ret)
	{  
		ret->autorelease();  
		return ret;  
	}  

	CC_SAFE_DELETE(ret); 
	return nullptr;  
}

bool AddJoint::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

bool AddJoint::addJoint(Scene* _scene, Node* sp1)
{
	Vec2 offset = sp1->getPosition();
	Node* node = Node::create();
    PhysicsBody* box = PhysicsBody::create();
    node->setPhysicsBody(box);
    box->setDynamic(false);
    node->setPosition(Point::ZERO);
    this->addChild(node);
    int width = 10, height = 10;
	box->addShape(PhysicsShapeEdgeBox::create(Size(width, height), PHYSICSSHAPE_MATERIAL_DEFAULT, 1, offset-Vec2(0, 20)));
                    
	_scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1->getPhysicsBody(), box, sp1->getPosition()));
	return true;
}

bool AddJoint::addJoint(Scene* _scene, Node* sp1, Node* sp2)
{
	int width = 0, height = 0;
	auto node2 = Sprite::create("stick.png");
    PhysicsBody* box2 = PhysicsBody::create();
    node2->setPhysicsBody(box2);
    box2->setDynamic(true);
	node2->setPosition(sp1->getPosition() + Vec2(0, sp1->getContentSize().height/2 + node2->getContentSize().height/2 ));
    this->addChild(node2);
	box2->addShape(PhysicsShapeBox::create(node2->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0, 0)));

	auto node1 = Sprite::create();
    PhysicsBody* box1 = PhysicsBody::create();
    node1->setPhysicsBody(box1);
    box1->setDynamic(false);
	node1->setPosition(node2->getPosition() + Vec2(0, node2->getContentSize().height/2 + 5));
    this->addChild(node1);
	box1->addShape(PhysicsShapeEdgeBox::create(Size(width+10, height+10), PHYSICSSHAPE_MATERIAL_DEFAULT, 1, Vec2(0, 0)));

	PhysicsJointDistance* jointOne = PhysicsJointDistance::construct(box1, box2, Point(0,0), Point(0,node2->getContentSize().height/2));
	_scene->getPhysicsWorld()->addJoint(jointOne);
	
	PhysicsJointDistance* jointTwo = PhysicsJointDistance::construct(sp1->getPhysicsBody(), box2, Point(0,sp1->getContentSize().height/2), Point(0,-node2->getContentSize().height/2));
	_scene->getPhysicsWorld()->addJoint(jointTwo);

	PhysicsJointDistance* jointThree = PhysicsJointDistance::construct(sp1->getPhysicsBody(), box1, Point(0, -sp1->getContentSize().height/2), Point(0,0));
	_scene->getPhysicsWorld()->addJoint(jointThree);

	PhysicsJointDistance* jointFour = PhysicsJointDistance::construct(sp1->getPhysicsBody(), box1, Point(0, sp1->getContentSize().height/2), Point(0,0));
	_scene->getPhysicsWorld()->addJoint(jointFour);

	/*PhysicsJointDistance* joinTwo = PhysicsJointDistance::construct(sp1->getPhysicsBody(), box1, Point(0,-sp1->getContentSize().height/2), Point(0,0));
	getScene()->getPhysicsWorld()->addJoint(joinTwo);
	log("== tone");

	Node* node2 = Node::create();
    PhysicsBody* box2 = PhysicsBody::create();
    node2->setPhysicsBody(box2);
    box2->setDynamic(false);
    node2->setPosition(Point(460,600));
    this->addChild(node2);
	box2->addShape(PhysicsShapeEdgeBox::create(Size(width+10, height+10), PHYSICSSHAPE_MATERIAL_DEFAULT, 1, Vec2(460, 400)));


	PhysicsJointDistance* jointOne = PhysicsJointDistance::construct(sp1->getPhysicsBody(), box1, Point(0,100), Point(0,0));
    _scene->getPhysicsWorld()->addJoint(jointOne);

	//PhysicsJointDistance* jointThree = PhysicsJointDistance::construct(sp2->getPhysicsBody(), sp1->getPhysicsBody(), Point(0,-100), Point(-150,10));
    //_scene->getPhysicsWorld()->addJoint(jointThree);*/

	return true;	
}