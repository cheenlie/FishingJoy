#include "Fish.h"
#include "StaticData.h"

USING_NS_CC;



enum{
	k_Action_Animate = 0,
	k_Action_MoveTo     //the flag of stop action
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

	//1,2,3���������ǲ��Ŷ������ھ����ϲ���һ������animation��
	CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);//1
	fishAnimate->setTag(k_Action_Animate);
	_fishSprite = CCSprite::create();//2
	this->addChild(_fishSprite);
	//CCRepeatForever��CCAnimate���и��ϣ��ﵽ����ѭ�����ŵ�Ч��
	_fishSprite->runAction(CCRepeatForever::create(fishAnimate));//3

	return true;
}

void Fish::moveTo(cocos2d::CCPoint destination)
{
	//ϸϸ���,����ڵ���ô����ʼֵ����question
	CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());

	float speed = ccpDistance(destination, start)/100;   //��������point��ľ���
	CCMoveTo* moveTo = CCMoveTo::create(speed,destination);  //�ƶ���
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));//�����ص�����

	CCFiniteTimeAction* seq = CCSequence::create(moveTo, callFunc, NULL);//�����ƶ�����
	seq->setTag(k_Action_MoveTo);//����ACtion�Ļ��ǩ
	this->runAction(seq);  //��������ʱ����˶��켣���С�FiniteTimeActon

}

void Fish::moveEnd()
{
	this->getParent()->removeChild(this,false);
}

void Fish::reset()
{
	this->setRotation(0);
	this->setVisible(true);
}

CCRect Fish::getCollisionArea()
{
	CCAssert(this->getParent(),"you should call this after add it as a child");

	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize size = _fishSprite->getContentSize();  //get the size of fishsprite

	return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);
}


//show the caught flush
void Fish::beCaught()
{
	this->stopActionByTag(k_Action_MoveTo);   //set the flag of stop action
	CCDelayTime* delayTime = CCDelayTime::create(1.0);  //delay one second
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fish::beCaught_CallFunc));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime,callFunc,NULL);

	CCBlink* blink = CCBlink::create(1.0,8); //set blink time,during 1 second
	CCFiniteTimeAction* spawn = CCSpawn::create(seq,blink,NULL);

	this->runAction(spawn);
}


//after  caught the fishes, remove fish from store
void Fish::beCaught_CallFunc()
{
	this->getParent()->removeChild(this, false);
}