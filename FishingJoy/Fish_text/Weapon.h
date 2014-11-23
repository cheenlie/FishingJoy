#ifndef __FishingJoy__Weapon__
#define __FishingJoy__Weapon__
#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
#include "FishingNet.h"

enum{
	k_Weapon_Status_None = 0,
	k_Weapon_Status_Bullet,
	k_Weapon_Status_FishingNet
};

class Weapon :public cocos2d::CCNode
{
public:
	static Weapon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type = k_Cannon_Type_1);

	//���ƺ���
	bool shootTo(cocos2d::CCPoint touchLocation);
	void aimAt(cocos2d::CCPoint target);

	void end();

	int weaponStatus();

	CC_SYNTHESIZE_READONLY(Cannon*,_cannon,Cannon);
	CC_SYNTHESIZE_READONLY(Bullet*, _bullet, Bullet);
	CC_SYNTHESIZE_READONLY(FishingNet*,_fishingNet,FishingNet);
	
	int getCannonType();
};

#endif