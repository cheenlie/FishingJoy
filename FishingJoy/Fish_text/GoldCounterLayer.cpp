#include "GoldCounterLayer.h"
#include "Counter.h"
USING_NS_CC;

GoldCounterLayer* GoldCounterLayer::create(int number)
{
	GoldCounterLayer* goldCounterLayer = new GoldCounterLayer(); //默认的构造函数
	goldCounterLayer->init(number);
	goldCounterLayer->autorelease();
	return goldCounterLayer;
}
bool GoldCounterLayer::init(int number)
{
	int fontSize = 16;
	CCLabelTTF* goldLabel = CCLabelTTF::create("金币:", "Thonburi", fontSize);
	this->addChild(goldLabel);
	CCSize goldLabelSize = goldLabel->getContentSize();

	for (int i = 0; i < 6; i++){  
		int count = 10;   
		CCArray* presenters = CCArray::createWithCapacity(count);
		for (int j = 0; j < count; j++){
			CCLabelTTF* label = CCLabelTTF::create(CCString::createWithFormat("%d",j)->getCString(), "Thonburi", fontSize);
			presenters->addObject(label);
		}
		Counter* counter = Counter::create(presenters);
		counter->setPosition(CCPointMake(goldLabelSize.width*0.8+fontSize*0.75*i, 0));
		this->addChild(counter, 0, i);
	}
	this->setNumber(number);
	return true;
}
void GoldCounterLayer::setNumber(int number, int ceiling)
{
	number = MIN(ceiling, number);
	number = MAX(number, 0);  //get positive number;
	_number = number;
	for (int i = 0; i < 6;i++)  //??question, why it cycle 6 times?  A: six Counter.
	{
		Counter* counter = (Counter*)this->getChildByTag(i);
		int digit = _number / (int)(pow(10.0, 6 - i - 1)) % 10;
		counter->setDigit(digit);
	}
}

