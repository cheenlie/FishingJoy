#ifndef __FishingJoy__PanelLayer__
#define __FishingJoy__PanelLayer__
#include "cocos2d.h"
#include "GoldCounterLayer.h"
class PanelLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(PanelLayer);
	bool init();

	CC_SYNTHESIZE_READONLY(GoldCounterLayer*,_goldCounterLayer,GoldCounterLayer);
protected:
	void pause(cocos2d::CCObject* pSender);
};

#endif /* defined(__FishingJoy__PanelLayer__) */
