#ifndef __FishingJoy__FishLayer__

#define __FishingJoy__FishLayer__
#include "cocos2d.h"

class FishLayer :public cocos2d::CCLayer
{
public:
	CREATE_FUNC(FishLayer);
	bool init(); 
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, _fishes, Fishes);//synthesize(�ϳ�)
	~FishLayer();
protected:
	void addFish(float dt);
};

#endif