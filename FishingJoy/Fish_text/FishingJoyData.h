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
	"set + funName" is the name of the setter.  //��cpp��������set+funName����
	*/

	CC_SYNTHESIZE(int, _gold, Gold);
	CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
	CC_SYNTHESIZE(float, _musicVolume, MusicVolume);

	void purge();

	/**
	*	@brief	 ��Gold�Ĳ���
	*
	*	@param 	delta 	����ֵ����
	*/
	void alterGold(int delta);

	/**
	*	@brief	 �����ݴ��ڴ汣�浽�ⲿ�ļ���
	*/
	void flush();
	void reset();
protected:
	FishingJoyData();
	~FishingJoyData();
	bool init();
};