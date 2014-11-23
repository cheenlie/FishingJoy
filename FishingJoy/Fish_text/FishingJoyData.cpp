#include "FishingJoyData.h"
#include "StaticData.h"
USING_NS_CC;

static FishingJoyData* _shareFishingJoyData = NULL;

//ʵ��.h�ļ��ж���ķ���
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

//���
void FishingJoyData::purge()
{
	CC_SAFE_RELEASE_NULL(_shareFishingJoyData);
}

//�������Ϸ���ݽ��г�ʼ��
bool FishingJoyData::init()
{
	//CCUserDefault����USING_NS_CC�����ռ���������
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
	//�������ַ������͵ļ�ֵ��Ĭ�ϲ�������ʾ�Ҳ�����Ӧ��ֵʱ���ص�ֵ��
	CCUserDefault::sharedUserDefault()->setFloatForKey("sound", this->getSoundVolume());
	CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", this->getIsBeginner());
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gold", this->getGold());
	CCUserDefault::sharedUserDefault()->setFloatForKey("music", this->getMusicVolume());

	//�ڳ�������̨ʱ����flush��������ʱ�������ݡ�����
	CCUserDefault::sharedUserDefault()->flush();

	//ֻ�����ⲿ�ļ�����ʱ���Ŵ�CCUserDefault����������ɾ��CCUserDefault���ݣ����������Ĺ���
	CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}