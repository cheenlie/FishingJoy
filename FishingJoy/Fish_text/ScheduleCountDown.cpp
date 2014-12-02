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

	//����cocos2d-x�ṩ��schedule������ÿ����¼�����һ�μ�����жϡ�
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

		//����ScheduleCounterDelegate��һ��ʵ����Ȼ�����cocos2d-x�ṩ��һ��schedule����
		_target->scheduleTimeUp();
	}
	_target->setScheduleNumber(_curTime);
}