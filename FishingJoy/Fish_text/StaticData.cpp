#include "StaticData.h"
USING_NS_CC;
using namespace std;//������׼�⺯���ռ�

#define STATIC_DATA_PATH "static_data.plist"

static StaticData* _sharedStaticData = NULL;

StaticData* StaticData::sharedStaticData()
{
	if (_sharedStaticData == NULL)
	{
		_sharedStaticData = new StaticData();
		_sharedStaticData->init();
	}
	return _sharedStaticData;

}

StaticData::StaticData()
{
	_staticDataPath =STATIC_DATA_PATH ;
}

StaticData::~StaticData()
{
	CC_SAFE_RELEASE_NULL(_dictionary);
}

bool StaticData::init()
{
	_dictionary = CCDictionary::createWithContentsOfFile(_staticDataPath.c_str());
	CC_SAFE_RETAIN(_dictionary);
	return true;
}

const char* StaticData::stringFromKey(string key)
{
	//CCDictionary�����ù�ϣ���㷨������CCObject�����һ���࣬����Ч�������������Ĵ洢���ѯ����
	return _dictionary->valueForKey(key)->getCString();
}

int StaticData::intFromKey(string key)
{
	return _dictionary->valueForKey(key)->intValue();
}

float StaticData::floatFromKey(string key)
{
	return _dictionary->valueForKey(key)->floatValue();
}

void StaticData::purge()
{
	CC_SAFE_RELEASE_NULL(_sharedStaticData);
}