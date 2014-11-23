#include "GameScene.h"
#include "StaticData.h"
#include "FishingJoyData.h"

#include "Fish.h"

USING_NS_CC;


//todo 预载入资源，实现StartScene后将其删除
void GameScene::preloadResources()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fishingjoy_resource.plist");

	int frameCount = STATIC_DATA_INT("fish_frame_count");
	for (int type = k_Fish_Type_Red; type < k_Fish_Type_Count; type++){
		CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);
		for (int i = 0; i < frameCount; i++){
			CCString* filename = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_name_format"), type, i);
			CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
			spriteFrames->addObject(spriteFrame);
		}

		//CCAnimation只用于存放动画，真正能让动画播放起来的是动作类CCAnimate，CCAnimate只能由CCSprite及其子类播放
		CCAnimation* fishAnimation = CCAnimation::createWithSpriteFrames(spriteFrames);
		fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
		CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), type);
		CCAnimationCache::sharedAnimationCache()->addAnimation(fishAnimation, animationName->getCString());
	}

}

bool GameScene::init()
{
	preloadResources();
	if (CCScene::init())
	{
		/*
		对之前的GameScene场景的层次分离图,用这个方法创建下面五个类，但是都是继承自CCLayer类
		*/
		_backgroundLayer = BackgroundLayer::create();
        this->addChild(_backgroundLayer);

		_fishLayer = FishLayer::create();
		this->addChild(_fishLayer);

		_cannonLayer = CannonLayer::create();
		this->addChild(_cannonLayer);

		_panelLayer = PanelLayer::create();
		this->addChild(_panelLayer);

		_menuLayer = MenuLayer::create();
		CC_SAFE_RETAIN(_menuLayer);

		_touchLayer = TouchLayer::create();
		this->addChild(_touchLayer);

		this->scheduleUpdate();//每一个frame都会调用这个方法

		return true;
	}
	return false;
}

void GameScene::pause()
{
	this->operateAllSchedulerAndActions(this,k_Operate_Pause );
	this->addChild(_menuLayer);
}

void GameScene::resume()
{
	this->operateAllSchedulerAndActions(this,k_Operate_Resume);
	this->removeChild(_menuLayer, false);

}

void GameScene::sound()
{
}
void GameScene::music()
{
}
void GameScene::reset()
{
}
void GameScene::transToMainMenu()
{
}
GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_menuLayer);
}
//暂停主场景中的动作和计时器
void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
	if (node->isRunning()){
		switch (flag){
		case k_Operate_Pause:

			//递归遍历渲染树中的所有节点
			node->pauseSchedulerAndActions(); //
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;

		}
	}
}

void GameScene::cannonAimAt(CCPoint target)
{
	_cannonLayer->aimAt(target);
	//_cannonLayer()->aimAt(target);//会弹出错误：明显 调用的 表达式的括号 必须具有（指针）函数类型
}

void GameScene::cannonShootTo(CCPoint target)
{
	_cannonLayer->shootTo(target);
}




