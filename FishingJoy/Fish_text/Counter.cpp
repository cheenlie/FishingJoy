#include "Counter.h"
#include "GL\glew.h"
USING_NS_CC;

enum{
	k_Counter_Action=0
};

Counter* Counter::create(CCArray* presenters,int digit )
{
	Counter* counter =new Counter();
	counter->init(presenters,digit);
	counter->autorelease();
	return counter;
}

bool Counter::init(CCArray* prestenter,int digit)
{
	_presenters = CCNode::create();  //save 0-9 numbers as a node
	for (int i = 0; i < 10; i++){   //ten numbers order as 0 to 10.
		CCNode* node = (CCNode*)prestenter->objectAtIndex(i);
		int y = node->getContentSize().height*i;  
		node->setPosition(CCPointMake(0,y));
		_presenters->addChild(node,0,i);   //save prestenter's data to _presenters
	}
	this->addChild(_presenters);
	this->setDigit(digit);
	return true;
}

Counter::Counter()
{
	_digit = 1;
}

int Counter::getDigit()
{
	return _digit;
}

void Counter::setDigit(int digit)
{
	if (_digit != digit)
	{
		_digit = digit;
		animation(_digit);
	}
}

//改变数字时播放滚动动画
void Counter::animation(int digit)
{
	//"_presenters;"存放0-9数字对应的节点
	CCNode* presenter = _presenters->getChildByTag(digit);

	CCPoint dest = presenter->getPosition();
	this->stopActionByTag(k_Counter_Action);   //set tag with this layer
	CCMoveTo* moveTo = CCMoveTo::create(0.5,CCPointMake(0,-dest.y));

	_presenters ->runAction(moveTo); //node's action.

}

void Counter::visit()
{
	glEnable(GL_SCISSOR_TEST);
	CCNode* presenter = _presenters->getChildByTag(_digit);
	CCSize size = presenter->getContentSize();
	CCPoint location = this->getParent()->convertToWorldSpace(CCPointMake(this->getPosition().x - size.width*0.5, this->getPosition().y - size.height*0.5));
	glScissor(location.x, location.y, size.width, size.height);
	CCNode::visit();
	glDisable(GL_SCISSOR_TEST);
}