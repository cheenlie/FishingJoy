#ifndef __FishingJoy__MenuLayer__
#define __FishingJoy__MenuLayer__
#include "cocos2d.h"
class MenuLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(MenuLayer);
	bool init();

	//�������ֺ���Ч��ť��״̬
	void setSoundAndMusicVolume(float soundVolume, float musicVolume);
protected:
	void createBackground();
	void createMenu();

	void resume(cocos2d::CCObject* pSender);
	void mainMenu(cocos2d::CCObject* pSender);
	void sound(cocos2d::CCObject* pSender);
	void music(cocos2d::CCObject* pSender);
	void reset(cocos2d::CCObject* pSender);

	//���ش�����
	cocos2d::CCMenuItemToggle* _sound;
	cocos2d::CCMenuItemToggle* _music;


};

#endif /* defined(__FishingJoy__MenuLayer__) */