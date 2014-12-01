#ifndef __FishingJoy__PanelLayer__
#define __FishingJoy__PanelLayer__
#include "cocos2d.h"
#include "GoldCounterLayer.h"
#include "ScheduleCountProtocol.h"

class PanelLayer : public cocos2d::CCLayer,public ScheduleCounterDelegate
{
public:
	CREATE_FUNC(PanelLayer);
	bool init();

	CC_SYNTHESIZE_READONLY(GoldCounterLayer*,_goldCounterLayer,GoldCounterLayer);

	//ScheduleCounterDelegate,继承此（ScheduleCounterDelegate）协议，并在.cpp文件中实现这两个方法
	void scheduleTimeUp();
	void setScheduleNumber(int number);
protected:
	void pause(cocos2d::CCObject* pSender);
	cocos2d::CCLabelTTF*  _scheduleLabel;
};

#endif /* defined(__FishingJoy__PanelLayer__) */
