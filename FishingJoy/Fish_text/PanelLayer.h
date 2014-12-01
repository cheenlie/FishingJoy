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

	//ScheduleCounterDelegate,�̳дˣ�ScheduleCounterDelegate��Э�飬����.cpp�ļ���ʵ������������
	void scheduleTimeUp();
	void setScheduleNumber(int number);
protected:
	void pause(cocos2d::CCObject* pSender);
	cocos2d::CCLabelTTF*  _scheduleLabel;
};

#endif /* defined(__FishingJoy__PanelLayer__) */
