#ifndef __FishingJoy__Counter__
#define __FishingJoy__Counter__
#include "cocos2d.h"

class Counter : public cocos2d::CCNode
{
public:
	CC_PROPERTY(int, _digit, Digit);
protected:

	//���0-9���ֶ�Ӧ�Ľڵ�
	cocos2d::CCNode* _presenters;

	//�ı�����ʱ���Ź�������
	void animation(int digit);
};

#endif