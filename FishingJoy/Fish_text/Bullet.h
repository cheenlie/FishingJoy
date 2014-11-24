#ifndef __FishingJoy__Bullet__
#define __FishingJoy__Bullet__
#include "cocos2d.h"



class Bullet:public cocos2d::CCNode
{
public:
	CREATE_FUNC(Bullet);
	//void init();//时上面就会报错，报表达式必须包含bool;当没有init()函数时，报没有init函数,所以CREATE_FUNC定义函数时包含了init函数
	bool init();

	//子弹飞行
	void flyTo(cocos2d::CCPoint target);
	//使子弹结束飞行
	void end();

	cocos2d::CCPoint getCollisionPoint();

protected:
	cocos2d::CCSprite* _bulletSprite;

};

#endif