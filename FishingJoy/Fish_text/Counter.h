#ifndef __FishingJoy__Counter__
#define __FishingJoy__Counter__
#include "cocos2d.h"

class Counter : public cocos2d::CCNode
{
public:
	CC_PROPERTY(int, _digit, Digit);
protected:

	//存放0-9数字对应的节点
	cocos2d::CCNode* _presenters;

	//改变数字时播放滚动动画
	void animation(int digit);
};

#endif