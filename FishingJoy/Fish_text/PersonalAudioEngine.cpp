#include "PersonalAudioEngine.h"
#include "FishingJoyData.h"
#include "StaticData.h"
USING_NS_CC;
static PersonalAudioEngine* _sharedEngine = NULL;   //??question, why don't put it in .h file?

//using namespace CocosDenshion;


PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
	if (_sharedEngine == NULL){
		_sharedEngine = new PersonalAudioEngine();
		_sharedEngine->init();
	}
	return _sharedEngine;
}

//如果在.h文件中声明了构造函数那么在要new一个新对象前，就必须实现构造函数。
PersonalAudioEngine::PersonalAudioEngine()
{

}
PersonalAudioEngine::~PersonalAudioEngine()
{

}

bool PersonalAudioEngine::init()
{
	this->preloadBackgroundMusic(STATIC_DATA_STRING("bg_music"));  
	//preload volume source into effective buffer
	this->preloadEffect(STATIC_DATA_STRING("sound_button"));
	this->preloadEffect(STATIC_DATA_STRING("button_shot"));

	this->setBackgroundMusicVolume(FishingJoyData::shareFishingJoyData()->getMusicVolume());
	this->setEffectsVolume(FishingJoyData::shareFishingJoyData()->getSoundVolume());

	return true;
}

void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
	FishingJoyData::shareFishingJoyData()->setMusicVolume(volume);
}

//rewrite setEffectsVolume function
void PersonalAudioEngine::setEffectsVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	FishingJoyData::shareFishingJoyData()->setSoundVolume(volume);
}
