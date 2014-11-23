
#ifndef __FishingJoy__TouchLayer__
#define __FishingJoy__TouchLayer__
#include "cocos2d.h"

//#include "GameScene.h"   //加上这一句，GameScene.h中“ TouchLayer* _touchLayer;”这个会报错，类型如下：
                           //error C4430: 缺少类型说明符 - 假定为 int.注意:  C++ 不支持默认 int
						   //****猜测：头文件引入出的问题？？   待继续研究
USING_NS_CC;

class GameScene; //添加到GameScene中；如果没这行第36行（GameScene* getGameScene();）会报错，类型如上：C4430

class TouchLayer : public cocos2d::CCLayer
{
public:

	CREATE_FUNC(TouchLayer);
	bool init();

	//只需实现单点触摸，因此只需实现CCTargetedTouchDelegate，如下三行代码来实现CCTargetedTouchDelegate（三个都为回调函数）
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);//采用的是带目标的触摸事件
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);


	//重载setTouchEnabled函数，便于随时打开和关闭触摸， 既开启、关闭触摸的接口
	void setTouchEnabled(bool flag);
protected:

	GameScene* getGameScene();
	cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch* touch);
};
#endif