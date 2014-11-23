#include "MenuLayer.h"
#include "StaticData.h"
#include "GameScene.h"
#include "cocos2d.h"
USING_NS_CC;

//使用CCMenue来为菜单添加按钮
void MenuLayer::createMenu()
{
	int fontSize = 32;
	CCString* fontName = CCString::create("Thonburi");

	CCMenuItemLabel* resume = CCMenuItemLabel::create(CCLabelTTF::create("Resume", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::resume));

	CCMenuItemLabel* mainMenu = CCMenuItemLabel::create(CCLabelTTF::create("Main Menu", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::mainMenu));

	CCMenuItemLabel* soundOn = CCMenuItemLabel::create(CCLabelTTF::create("Sound On", fontName->getCString(), fontSize));
	CCMenuItemLabel* soundOff = CCMenuItemLabel::create(CCLabelTTF::create("Sound Off", fontName->getCString(), fontSize));
	_sound = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::sound), soundOff, soundOn, NULL);

	CCMenuItemLabel* musicOn = CCMenuItemLabel::create(CCLabelTTF::create("Music On", fontName->getCString(), fontSize));
	CCMenuItemLabel* musicOff = CCMenuItemLabel::create(CCLabelTTF::create("Music Off", fontName->getCString(), fontSize));
	_music = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::music), musicOff, musicOn, NULL);

	CCMenuItemLabel* reset = CCMenuItemLabel::create(CCLabelTTF::create("Reset", fontName->getCString(), fontSize), this, menu_selector(MenuLayer::reset));

	CCMenu* menu = CCMenu::create(resume, mainMenu, _sound, _music, reset, NULL);
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu);
}

bool MenuLayer::init()
{
	if (CCLayer::init())
	{
		this->createBackground();
		this->createMenu();
		return true;
	}
	return false;
}

//使用CCLayerColor来添加半透明背景的功能
void MenuLayer::createBackground()
{

	//ccc4为cocos2d-x定义的一个颜色结构体，它的四个参数分别是RGBA的值，范围为0~255，这里定义一个透明度为50%的黑色背景
	CCLayerColor* colorBackground = CCLayerColor::create(ccc4(0, 0, 0, 128));
	this->addChild(colorBackground);
}

//剩余的按钮都以CCMenuItem的形式实现，同样按钮的回调函数只是将信息传递到GameScence中，由GameScence进行实质性操作


//让音乐和音效的开关状态适配于数据中的音量大小,传递进去的是音量参数
void MenuLayer::setSoundAndMusicVolume(float soundVolume, float musicVolume)
{
	bool soundFlag = soundVolume > 0;
	bool musicFlag = musicVolume > 0;
	_sound->setSelectedIndex(soundFlag);
	_music->setSelectedIndex(musicFlag);


}

void MenuLayer::resume(cocos2d::CCObject* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->resume();
}

void MenuLayer::mainMenu(cocos2d::CCObject* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->transToMainMenu();
}

void MenuLayer::sound(cocos2d::CCObject* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->sound();
}

void MenuLayer::music(cocos2d::CCObject* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->music();
}


void MenuLayer::reset(cocos2d::CCObject* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->reset();
}
