#include "ScheduleCountDown.h"
#include "PanelLayer.h"
#include "GameScene.h"
USING_NS_CC;

ScheduleCountDown* ScheduleCountDown::create(ScheduleCounterDelegate* target, int perimeter, bool loop)
{
	ScheduleCountDown* scheduleCountDown = new ScheduleCountDown();
	scheduleCountDown->init( target,  perimeter, loop);
	scheduleCountDown->autorelease();
	return scheduleCountDown;

}

bool ScheduleCountDown::init(ScheduleCounterDelegate* target, int perimeter, bool loop)
{
	_target = target;
	_maxTime = perimeter;
	_curTime = _maxTime;
	_loop = loop;

	//调用cocos2d-x提供的schedule函数，每秒对事件进行一次计算和判断。
	this->schedule(schedule_selector(ScheduleCountDown::schedulePerSecond), 1.0f);
	return true;
}

void ScheduleCountDown::schedulePerSecond(float delta)
{
	_curTime--;
	if (_curTime <= 0){

		if (this->getLoop()){
			_curTime = _maxTime;
		}
		else{
			this->unschedule(schedule_selector(ScheduleCountDown::schedulePerSecond));
		}

		//保存ScheduleCounterDelegate的一个实例，然后调用cocos2d-x提供的一个schedule函数
		_target->scheduleTimeUp();
	}
	_target->setScheduleNumber(_curTime);
}