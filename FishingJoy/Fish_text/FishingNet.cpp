#include "FishingNet.h"
#include "StaticData.h"
USING_NS_CC;

bool FishingNet::init()
{
	_fishingNetSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("fishing_net"));
	this->addChild(_fishingNetSprite);
	return true;
}