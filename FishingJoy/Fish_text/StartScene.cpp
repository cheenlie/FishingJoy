#include "cocos2d.h"
#include "StartScene.h"
#include "Fish.h"
#include "StaticData.h" //STATIC_DATA_STRING在这个头文件里
#include "GameScene.h"
#include "PersonalAudioEngine.h"

USING_NS_CC;

CCScene* StartLayer::scene()
{
	CCScene* scene = CCScene::create();
	StartLayer* layer = StartLayer::create();
	
	//场景里面包括层
	scene->addChild(layer);
	return scene;
}

bool StartLayer::init()
{
	if (CCLayer::init())
	{
		//获得屏幕大小
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite* background = CCSprite::create(STATIC_DATA_STRING("background"));
		background->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.5));
		this->addChild(background);

		CCSprite* title = CCSprite::create(STATIC_DATA_STRING("title"));
		title->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.7));
		this->addChild(title);

		//how many frames were called since the director started
		if (CCDirector::sharedDirector()->getTotalFrames()<10){
			//异步把所有图片加入缓存；另一种方法是，使用Cocos2d-x配套发布pthread的第三方库
			CCTextureCache::sharedTextureCache()->addImageAsync(STATIC_DATA_STRING("fishingjoy_texture"), this, callfuncO_selector(StartLayer::loading));
			//设置进度条的背景
			CCSprite* progressBg = CCSprite::create(STATIC_DATA_STRING("progress_bg"));

			//进度条显示数字精度
			_progressFg = CCLabelTTF::create("0/100","Thonburi",16);
			_progressFg->setColor(ccc3(0,0,0));
			
			//create函数在progressbar中被重写了
			_progressBar = ProgressBar::create(this,CCSprite::create(STATIC_DATA_STRING("progress_bar")));
			_progressBar->setBackground(progressBg); //设置进度条背景
			_progressBar->setForeground(_progressFg);//设置进度条前景
			_progressBar->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
			_progressBar->setSpeed(100.0);
			this->addChild(_progressBar);

			//等待加载背景音乐
		}
		else{
			this->initializationCompleted();
		}
		return true;
	}
	return false;
}

void StartLayer::loading(CCObject* pObj)
{
	_progressBar->progressTo(100.0);
}

void StartLayer::loadingFinished()
{
	this->cacheInit();
	this->initializationCompleted();
}

//这是原函数"void GameScene::preloadResources()“这个里面预加载资源的函数
void StartLayer::cacheInit()
{
	//把精灵放到cache中
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fishingjoy_resource.plist");

	//在文件中把frame的总数读取出来
	int frameCount = STATIC_DATA_INT("fish_frame_count");
	for (int type = k_Fish_Type_Red; type < k_Fish_Type_Count; type++){
		CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);
		for (int i = 0; i < frameCount; i++){
			CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_name_format"),type,i);
			//把读出的fame_name初始化为sprite
			CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName->getCString());
			spriteFrames->addObject(spriteFrame);
		}
		//CCAnimation只用于存放动画，真正能让动画播放起来的是动作类CCAnimate，CCAnimate只能由CCSprite及其子类播放
		CCAnimation* fishAnimation = CCAnimation::createWithSpriteFrames(spriteFrames);
		fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
		CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), type);
		CCAnimationCache::sharedAnimationCache()->addAnimation(fishAnimation, animationName->getCString());
	}
}

void StartLayer::initializationCompleted()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemSprite* start = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("start_normal")), CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("start_selected")), this, menu_selector(StartLayer::transition));
	//加载开始按钮后，调用回调函数来加载另外一个层。
	CCMenu* menu = CCMenu::create(start, NULL);
	menu->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.4));

	//加载完了，去除进度条
	this->removeChild(_progressBar,true );
	this->addChild(menu);
	//把开始菜单放上去的同时打开背景音乐
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("bg_music"));

}

void StartLayer::transition(CCObject* pSender)
{
	//加载GameScene层。
	CCScene* scene = CCTransitionFadeDown::create(1.0f,GameScene::create());
	//换层
	CCDirector::sharedDirector()->replaceScene(scene);
}

void StartLayer::progressPercentageSetter(float percentage)
{

	CCString* str = CCString::createWithFormat("%d/100",(int)percentage);
	_progressFg->setString(str->getCString());
}