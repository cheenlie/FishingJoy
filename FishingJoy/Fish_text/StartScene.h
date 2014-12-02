#ifndef __FishingJoy__StartScene__
#define __FishingJoy__StartScene__
#include "cocos2d.h"
#include "ProgressBar.h"
#include "ProgressProtocol.h"

USING_NS_CC;

//在这里是层里包括场景，和CPP中scene函数里面的正好相反。
class StartLayer : public cocos2d::CCLayer, public ProgressDelegate
{
public:
	static cocos2d::CCScene* scene(); //这里用scene，和Gamescene里声明为scene一样，相当于create()
	bool init();
	CREATE_FUNC(StartLayer);

	//继承自ProgressProtocol的progressPercentageSetter接口，必须实现这个接口
	void progressPercentageSetter(float percentage);
	void loadingFinished();
protected:
	void loading(CCObject* pObj);
	ProgressBar* _progressBar;

	void cacheInit();
	void initializationCompleted();

	void transition(CCObject* pSender);
	cocos2d::CCLabelTTF* _progressFg;

};

#endif