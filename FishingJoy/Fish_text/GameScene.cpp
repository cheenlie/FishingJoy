#include "GameScene.h"
#include "StaticData.h"
#include "FishingJoyData.h"
#include "PersonalAudioEngine.h"

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
		//add touchLayer
		_touchLayer = TouchLayer::create();
		this->addChild(_touchLayer);

		//add panelLayer and set goal base plist file
		_panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::shareFishingJoyData()->getGold());
		//set sound and music data that from plist file
		_menuLayer->setSoundAndMusicVolume(FishingJoyData::shareFishingJoyData()->getSoundVolume(),FishingJoyData::shareFishingJoyData()->getMusicVolume());

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
	int type = _cannonLayer->getWeapon()->getCannon()->getType();
	int cost = (type + 1) * 1;
	int currentGold = FishingJoyData::shareFishingJoyData()->getGold();
	if (currentGold >= cost && _cannonLayer->shootTo(target)){
		PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_shot"));
		this->alterGold(-cost);
	}
	
}
void GameScene::alterGold(int delta)
{
	FishingJoyData::shareFishingJoyData()->alterGold(delta);
	_panelLayer->getGoldCounterLayer()->setNumber(FishingJoyData::shareFishingJoyData()->getGold());
}

void GameScene::update(float delat) //why program alway call this function? ?question
{
	checkOutCollision();
}

void GameScene::checkOutCollision()
{
	Weapon* weapon = _cannonLayer->getWeapon();
	if (weapon->weaponStatus() == k_Weapon_Status_Bullet){

		//1. whether bullet collision fish?
		//2. yes -> open fishingNet,check whether fishingNet collision fish ? 
		bool flag = this->checkOutCollisionBetweenFishesAndBullet();// the status of collision
		if (flag){
			this->checkOutCollisionBetweenFishesAndFishingNet();
		}
	}
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet()
{
	Weapon* weapon = _cannonLayer->getWeapon();// get weapon from cannonLayer, cannonLayer contain weapon
	CCPoint bulletCollision = weapon->getCollisionPoint();

	CCArray* fishes = _fishLayer->getFishes();  //get fishes from Arrary in the fishLayer
	CCObject* iterator;  //create a iterator type variable[����һ������������]
	CCARRAY_FOREACH(fishes,iterator){   //check every fish
		Fish* fish = (Fish*)iterator;
		if (fish->isRunning()){   //judge whether fish is in screen.

			CCRect fishCollisionArea = fish->getCollisionArea();

			//judge whether collision is happen
			bool isCollision = fishCollisionArea.containsPoint(bulletCollision);
			if (isCollision){
				weapon->end();
				return true;
			}
		}
	}
	return false;
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet()  //show the fishingNet
{
	Weapon* wepon = _cannonLayer->getWeapon();
	CCRect bulletCollision = wepon->getCollisionArea();
	CCArray* fishes = _fishLayer->getFishes();
	CCObject* iterator;
	CCARRAY_FOREACH(fishes,iterator){
		Fish* fish = (Fish*)iterator;
		if (fish->isRunning()){  //wheather fish is on screen
			CCRect fishCollisionArea = fish->getCollisionArea();
			bool isCollision = fishCollisionArea.intersectsRect(bulletCollision);
			if (isCollision){
				this->fishWillBeCaught(fish);
			}
		}
	}
}

void GameScene::fishWillBeCaught(Fish* fish)
{
	int weaponType = _cannonLayer->getWeapon()->getCannonType();  //get cannon's type
	int fishType = fish->getType();

	//??question, i don't know what's the function of percentage
	float fish_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("fish_percentage_format"),fishType)->getCString());
	float weapon_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"), weaponType)->getCString());
	float percentage = fish_percentage*weapon_percentage;
	if (CCRANDOM_0_1() < percentage)
	{
		fish->beCaught();
	}

}

