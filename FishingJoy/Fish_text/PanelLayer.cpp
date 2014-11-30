#include "GameScene.h"
#include "PanelLayer.h"
#include "StaticData.h"

USING_NS_CC;

bool PanelLayer::init()
{
	if (CCLayer::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		_goldCounterLayer = GoldCounterLayer::create();
		this->addChild(_goldCounterLayer);

		CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_selected")), this, menu_selector(PanelLayer::pause));
		CCMenu* menu = CCMenu::create(pause, NULL);
		this->addChild(menu);

		_goldCounterLayer->setPosition(CCPointMake(winSize.width*0.05, winSize.height*0.05));
		//CCSize��ʾ��С�ĺ���������ָ��
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

