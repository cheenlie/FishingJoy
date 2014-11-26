#include "Counter.h"
USING_NS_CC;

enum{
	k_Counter_Action=0
};

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