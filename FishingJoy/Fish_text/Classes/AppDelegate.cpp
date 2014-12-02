//
//  FishingJoyAppDelegate.cpp
//  FishingJoy
//
//  Created by Ringo_D on 12-9-8.
//  Copyright Martin Network 2012年. All rights reserved.
//

#include "AppDelegate.h"
#include "../StartScene.h"  //项目中文件位置和实际项目文件所在文件夹位置不一样
#include "cocos2d.h"
#include "../FishingJoyData.h"
#include "../GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
	// pDirector->enableRetinaDisplay(true);

	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	//CCScene *pScene = GameScene::create();
	//加了startscene后就换一种启动方式
	CCScene* pScene = StartLayer::scene();

	//run
	pDirector->runWithScene(pScene);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();

	FishingJoyData::shareFishingJoyData()->flush();
	// if you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
