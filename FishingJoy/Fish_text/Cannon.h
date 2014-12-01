#ifndef __FishingJoy__Cannon__
#define __FishingJoy__Cannon__
#include "cocos2d.h"
#include "Bullet.h"


//未被初始化的枚举值的值默认将比其前面的枚举值大1
typedef enum{
	k_Cannon_Type_1 = 0,
	k_Cannon_Type_2,
	k_Cannon_Type_Count,
	k_Cannon_Type_Invalid
}CannonType;

class Cannon :public cocos2d::CCNode
{
public:
	Cannon();
	~Cannon();
	static Cannon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type = k_Cannon_Type_1);

	CC_PROPERTY(CannonType, _type, Type);
	cocos2d::CCSprite* getCurCannonSprite();

	void aimAt(cocos2d::CCPoint target);
protected:
	cocos2d::CCArray* _cannonSprites;
}

#endif