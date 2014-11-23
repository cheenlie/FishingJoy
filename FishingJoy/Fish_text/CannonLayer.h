#ifndef __FishingJoy__CannonLayer__
#define __FishingJoy__CannonLayer__
#include "cocos2d.h"
#include "Weapon.h"

class CannonLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(CannonLayer);//这个地方没有init也不会报错
	bool init();
	CC_SYNTHESIZE_READONLY(Weapon*,_weapon,Weapon);

	bool shootTo(cocos2d::CCPoint touchLocation);
	void aimAt(cocos2d::CCPoint target);
protected:
	void switchCannon(cocos2d::CCObject* sender);
	cocos2d::CCMenuItemSprite* _subItem;
	cocos2d::CCMenuItemSprite* _addItem;
	

};

#endif /* defined(__FishingJoy__Cannon__) */