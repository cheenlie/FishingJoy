#include "FishingNet.h"
#include "StaticData.h"
USING_NS_CC;

bool FishingNet::init()
{
	_fishingNetSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("fishing_net"));
	this->addChild(_fishingNetSprite);
	return true;
}

void FishingNet::showAt(CCPoint pos)
{
	this->setPosition(pos);
	this->setScale(1.0f);
	this->setVisible(true);
	this->stopAllActions();// remove all actions from the  running  action list
	this->runAction(this->netAction());

}

//net flush
CCAction* FishingNet::netAction()
{
	CCDelayTime* delayTime = CCDelayTime::create(1.0);
	CCHide* hide = CCHide::create();

	CCFiniteTimeAction* seq = CCSequence::create(delayTime,hide,NULL);

	return seq;
}