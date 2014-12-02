#include "GameScene.h"
#include "PanelLayer.h"
#include "StaticData.h"
#include "ScheduleCountDown.h"

USING_NS_CC;

bool PanelLayer::init()
{
	if (CCLayer::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		_goldCounterLayer = GoldCounterLayer::create();
		this->addChild(_goldCounterLayer);

		//??question, why it import "this"?
		ScheduleCountDown* scheduleCountDown = ScheduleCountDown::create(this); 
		_scheduleLabel = CCLabelTTF::create("10", "Thonburi", 16);
		_scheduleLabel->addChild(scheduleCountDown);
		this->addChild(_scheduleLabel);

		CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_selected")), this, menu_selector(PanelLayer::pause));
		CCMenu* menu = CCMenu::create(pause, NULL);
		this->addChild(menu);

		_goldCounterLayer->setPosition(CCPointMake(winSize.width*0.05, winSize.height*0.05));
		//CCSize表示大小的函数，不是指针
		_scheduleLabel->setPosition(CCPointMake(winSize.width*0.8, winSize.height*0.05));

		CCSize pauseSize = pause->getContentSize();
		menu->setPosition(CCPointMake(winSize.width - pauseSize.width*0.5, pauseSize.height*0.5));
		return true;
	}
	return false;
	
}

void PanelLayer::pause(cocos2d::CCObject* pSender)
{
	GameScene* gameScence = (GameScene*)this->getParent();
	gameScence->pause();
}

//ScheduleCounterDelegate,继承此（ScheduleCounterDelegate）协议，并在.cpp文件中实现这两个接口，如scheduleTimeUp和setScheduleNumber方法
void PanelLayer::scheduleTimeUp()
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->scheduleTimeUp();
}

void PanelLayer::setScheduleNumber(int number)
{
	_scheduleLabel->setString(CCString::createWithFormat("%d", number)->getCString());
}