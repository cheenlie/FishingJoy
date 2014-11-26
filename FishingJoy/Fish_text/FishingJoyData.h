#include "cocos2d.h"

class FishingJoyData : public cocos2d::CCObject
{
public:
	static FishingJoyData* shareFishingJoyData();

	/*
	 We can use getter to read the variable, and use the setter to change the variable.
	 @param varType : the type of variable.
	 @param varName : variable name.
	 @param funName : "get + funName" is the name of the getter.
	"set + funName" is the name of the setter.  //在cpp函数中有set+funName函数
	*/

	CC_SYNTHESIZE(int, _gold, Gold);
	CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
	CC_SYNTHESIZE(float, _musicVolume, MusicVolume);

	void purge();

	/**
	*	@brief	 对Gold的操作
	*
	*	@param 	delta 	正负值均可
	*/
	void alterGold(int delta);

	/**
	*	@brief	 将数据从内存保存到外部文件中
	*/
	void flush();
	void reset();
protected:
	FishingJoyData();
	~FishingJoyData();
	bool init();
};