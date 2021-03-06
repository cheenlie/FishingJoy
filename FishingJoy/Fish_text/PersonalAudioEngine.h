
#ifndef __FishingJoy__PersonalAudioEngine__
#define __FishingJoy__PersonalAudioEngine__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

class PersonalAudioEngine : public CocosDenshion::SimpleAudioEngine
{
public:
	void setBackgroundMusicVolume(float volume);
	void setEffectsVolume(float volume);

	
	static PersonalAudioEngine* sharedEngine();
	bool init();

protected:
	PersonalAudioEngine();
	~PersonalAudioEngine();
};


#endif