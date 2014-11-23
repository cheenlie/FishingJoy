//#ifndef __FishingJoy__FishingNet__
//#define __FishingJoy__FishingNet__
//#include "cocos2d.h"
//
//class FishingNet : public cocos2d::CCNode
//{
//public:
//	CREATE_FUNC(FishingNet);
//	bool init();
//protected:
//	cocos2d::CCSprite *_fishingNetSprite;
//};
//#endif


#ifndef __FishingJoy__FishingNet__
#define __FishingJoy__FishingNet__
#include "cocos2d.h"


; class FishingNet : public cocos2d::CCNode
{
public:
	CREATE_FUNC(FishingNet);
	bool init();
protected:
	cocos2d::CCSprite *_fishingNetSprite;
};
#endif 