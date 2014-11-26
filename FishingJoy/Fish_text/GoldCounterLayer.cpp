#include "GoldCounterLayer.h"
#include "Counter.h"
USING_NS_CC;

bool GoldCounterLayer::init(int number)
{
	//begin next day
}

void GoldCounterLayer::setNumber(int number,int ceiling)
{
	number = MIN(number, ceiling);
	ceiling = MAX(number, ceiling);
	_number = number;
	for (int i = 0; i < 6;i++)  //??question, why it cycle 6 times?
	{
		Counter* counter = (Counter*)this->getChildByTag(i);
		int digit = _number / (int)(pow(10.0, 6 - i - 1)) % 10;
		counter->setDigit(digit);
	}
}