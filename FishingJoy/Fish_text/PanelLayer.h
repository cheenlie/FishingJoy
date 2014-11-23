#ifndef __FishingJoy__PanelLayer__
#define __FishingJoy__PanelLayer__
#include "cocos2d.h"
class PanelLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(PanelLayer);
	bool init();
protected:
	void pause(cocos2d::CCObject* pSender);
};

#endif /* defined(__FishingJoy__PanelLayer__) */
