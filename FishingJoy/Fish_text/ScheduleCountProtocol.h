#ifndef __FishingJoy__ScheduleCounterProtocol__
#define __FishingJoy__ScheduleCounterProtocol__

//所有使用倒计时功能的类，都将继承自ScheduleCounterDelegate类
class ScheduleCounterDelegate
{
public:
	/**
	*	@brief	    Required
	*/
	virtual void scheduleTimeUp() = 0;
	/**
	*	@brief	    Optional
	*
	*	@param 	number 	需要设置的数字
	*/
	virtual void setScheduleNumber(int number){ return; };
};


#endif