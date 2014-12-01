#ifndef __FishingJoy__ScheduleCountDown__
#define __FishingJoy__ScheduleCountDown__
#include "ScheduleCountProtocol.h"
#include "cocos2d.h"

class ScheduleCountDown : public cocos2d::CCNode
{
public:

	/**
	*	@param 	target 	ʵ��ScheduleCounterDelegate����
	*	@param 	perimeter 	����ʱ������
	*	@param 	loop 	�Ƿ�ѭ����
	*	@return
	*/
	static ScheduleCountDown* create(ScheduleCounterDelegate* target,int perimeter=60,bool loop=true);
	bool init(ScheduleCounterDelegate* target, int perimeter = 60, bool loop = true);

	CC_SYNTHESIZE(bool,_loop,Loop);
protected:
	//����ScheduleCounterDelegate��һ��ʵ����Ȼ�����cocos2d-x�ṩ��һ��schedule����
	ScheduleCounterDelegate* _target;
	//curent time
	int _curTime;
	//max time
	int _maxTime;
	void schedulePerSecond(float delta);

};


#endif