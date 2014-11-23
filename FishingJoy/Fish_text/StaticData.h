#include "cocos2d.h"


#define STATIC_DATA_STRING(key) StaticData::sharedStaticData()->stringFromKey(key)
#define STATIC_DATA_INT(key) StaticData::sharedStaticData()->intFromKey(key)
#define STATIC_DATA_FLOAT(key) StaticData::sharedStaticData()->floatFromKey(key)
#define STATIC_DATA_BOOLEAN(key) StaticData::sharedStaticData()->booleanFromKey(key)
#define STATIC_DATA_POINT(key) StaticData::sharedStaticData()->pointFromKey(key)
#define STATIC_DATA_RECT(key) StaticData::sharedStaticData()->rectFromKey(key)
#define STATIC_DATA_SIZE(key) StaticData::sharedStaticData()->sizeFromKey(key)

; class StaticData :public cocos2d::CCObject
{
public:
	static StaticData* sharedStaticData();  //定义本类类型的函数,以便以静态类型供外界访问。
	void purge();

	//定义接口，将重复性的操作进行封装
	const char* stringFromKey(std::string key);
	int intFromKey(std::string key);
	float floatFromKey(std::string key);
	bool booleanFromKey(std::string key);
	cocos2d::CCPoint pointFromKey(std::string key);
	cocos2d::CCRect rectFromKey(std::string key);
	cocos2d::CCSize sizeFromKey(std::string key);		 


	CC_SYNTHESIZE_READONLY(std::string,_staticDataPath,staticDataPath);
private:
	StaticData();
	~StaticData();
	bool init();
protected:
	cocos2d::CCDictionary* _dictionary;   //作用存储CCObject
};