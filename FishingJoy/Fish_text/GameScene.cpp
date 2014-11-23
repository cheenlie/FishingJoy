#include "GameScene.h"
#include "StaticData.h"
#include "FishingJoyData.h"

#include "Fish.h"

USING_NS_CC;


//todo Ԥ������Դ��ʵ��StartScene����ɾ��
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

		//CCAnimationֻ���ڴ�Ŷ������������ö��������������Ƕ�����CCAnimate��CCAnimateֻ����CCSprite�������ಥ��
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
		��֮ǰ��GameScene�����Ĳ�η���ͼ,���������������������࣬���Ƕ��Ǽ̳���CCLayer��
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

		this->scheduleUpdate();//ÿһ��frame��������������

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
//��ͣ�������еĶ����ͼ�ʱ��
void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
	if (node->isRunning()){
		switch (flag){
		case k_Operate_Pause:

			//�ݹ������Ⱦ���е����нڵ�
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
	//_cannonLayer()->aimAt(target);//�ᵯ���������� ���õ� ���ʽ������ ������У�ָ�룩��������
}

void GameScene::cannonShootTo(CCPoint target)
{
	_cannonLayer->shootTo(target);
}




