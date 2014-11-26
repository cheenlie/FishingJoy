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

//�ı�����ʱ���Ź�������
void Counter::animation(int digit)
{
	//"_presenters;"���0-9���ֶ�Ӧ�Ľڵ�
	CCNode* presenter = _presenters->getChildByTag(digit);

	CCPoint dest = presenter->getPosition();
	this->stopActionByTag(k_Counter_Action);   //set tag with this layer
	CCMoveTo* moveTo = CCMoveTo::create(0.5,CCPointMake(0,-dest.y));

	_presenters ->runAction(moveTo); //node's action.

}