#include "FishingJoyData.h"
#include "StaticData.h"
USING_NS_CC;

static FishingJoyData* _shareFishingJoyData = NULL;

//实现.h文件中定义的方法
FishingJoyData* FishingJoyData::shareFishingJoyData()
{
	if (_shareFishingJoyData == NULL){
		_shareFishingJoyData = new FishingJoyData();
		_shareFishingJoyData->init();
	}
	return _shareFishingJoyData;

}

FishingJoyData::FishingJoyData()
{

}

FishingJoyData::~FishingJoyData()
{
	this->flush();
}

//清空
void FishingJoyData::purge()
{
	CC_SAFE_RELEASE_NULL(_shareFishingJoyData);
}

//对玩家游戏数据进行初始化
bool FishingJoyData::init()
{
	//CCUserDefault是由USING_NS_CC命名空间引过来的
	_isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner", true);
	if ( _isBeginner == true)
	{
		this->reset();
		this->flush();
		this->setIsBeginner(false);
	}
	else
	{
		_isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
		_soundVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("sound");
		_musicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("music");
		_gold = CCUserDefault::sharedUserDefault()->getIntegerForKey("gold");
	}
	return true;
}

void FishingJoyData::reset()
{
	int gold = STATIC_DATA_INT("default_gold");
	this->setGold(gold);
	this->setIsBeginner(true);
	this->setMusicVolume(1);
	this->setSoundVolume(1);
	this->flush();
}

void FishingJoyData::flush()
{
	//参数，字符串类型的键值，默认参数（表示找不到对应键值时返回的值）
	CCUserDefault::sharedUserDefault()->setFloatForKey("sound", this->getSoundVolume());
	CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", this->getIsBeginner());
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gold", this->getGold());
	CCUserDefault::sharedUserDefault()->setFloatForKey("music", this->getMusicVolume());

	//在程序进入后台时调用flush方法，及时保存数据。？？
	CCUserDefault::sharedUserDefault()->flush();

	//只在与外部文件交互时，才打开CCUserDefault，用完后必须删除CCUserDefault数据，如下面语句的功能
	CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}