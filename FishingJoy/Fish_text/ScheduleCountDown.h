#ifndef __FishingJoy__ScheduleCountDown__
#define __FishingJoy__ScheduleCountDown__
#include "ScheduleCountProtocol.h"
#include "cocos2d.h"

class ScheduleCountDown : public cocos2d::CCNode
{
public:

	/**
	*	@param 	target 	实现ScheduleCounterDelegate的类
	*	@param 	perimeter 	倒计时的周期
	*	@param 	loop 	是否循环。
	*	@return
	*/
	static ScheduleCountDown* create(ScheduleCounterDelegate* target,int perimeter=60,bool loop=true);
	bool init(ScheduleCounterDelegate* target, int perimeter = 60, bool loop = true);

	CC_SYNTHESIZE(bool,_loop,Loop);
protected:
	//保存ScheduleCounterDelegate的一个实例，然后调用cocos2d-x提供的一个schedule函数
	ScheduleCounterDelegate* _target;
	//curent time
	int _curTime;
	//max time
	int _maxTime;
	void schedulePerSecond(float delta);

};


#endif