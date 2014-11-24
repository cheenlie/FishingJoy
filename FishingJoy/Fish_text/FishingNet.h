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

	//使FishingNet在屏幕上出现
	void showAt(cocos2d::CCPoint pos);
protected:
	cocos2d::CCSprite *_fishingNetSprite;

	cocos2d::CCAction* netAction();
};
#endif 