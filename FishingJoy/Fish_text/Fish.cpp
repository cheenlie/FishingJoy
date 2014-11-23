#include "Fish.h"
#include "StaticData.h"

USING_NS_CC;


//搞不懂这个枚举是拿来干嘛的
enum{
	k_Action_Animate = 0,
};

Fish* Fish::create(FishType type)
{
	Fish* fish = new Fish();
	fish->init(type);
	fish->autorelease();
	return fish;
}

bool Fish::init(FishType type)
{
	_type = type;
	CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), _type);
	CCAnimation* fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());

	//1,2,3连起来就是播放动画（在精灵上播放一个动画animation）
	CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);//1
	fishAnimate->setTag(k_Action_Animate);
	_fishSprite = CCSprite::create();//2
	this->addChild(_fishSprite);
	//CCRepeatForever对CCAnimate进行复合，达到无限循环播放的效果
	_fishSprite->runAction(CCRepeatForever::create(fishAnimate));//3

	return true;
}
