#ifndef __FishingJoy__GoldCounter__
#define __FishingJoy__GoldCounter__
#include "cocos2d.h"

class GoldCounterLayer : public cocos2d::CCNode
{
public:
	void setNumber(int number,int ceiling=999999);

	bool init(int number = 0);

	CC_SYNTHESIZE_READONLY(int, _number, Number);

protected:
	
};

#endif