#include "GameScene.h"
#include "PanelLayer.h"
#include "StaticData.h"

USING_NS_CC;

bool PanelLayer::init()
{
	if (CCLayer::init())
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_normal")),CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("pause_selected")),this,menu_selector(PanelLayer::pause));
		CCMenu* menu = CCMenu::create(pause, NULL);
		this->addChild(menu);

		//CCSize表示大小的函数，不是指针
		CCSize pauseSize = pause->getContentSize();
		menu->setPosition(CCPointMake(winSize.width-pauseSize.width*0.5,pauseSize.height*0.5));

		return true;
	}
	return false;
}

void PanelLayer::pause(cocos2d::CCObject* pSender)
{
	GameScene* gameScence = (GameScene*)this->getParent();
	gameScence->pause();
}