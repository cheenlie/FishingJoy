#include "cocos2d.h"
#include "TouchLayer.h"
#include "GameScene.h"
#include "TouchLayer.h"
USING_NS_CC;

GameScene* TouchLayer::getGameScene()
{
	return (GameScene*)this->getParent();
}

bool TouchLayer::init()
{
	this->setTouchEnabled(true);
	return true;
}

//重载setTouchEnabled函数，便于随时打开和关闭触摸
void TouchLayer::setTouchEnabled(bool flag)
{
	if (m_bIsTouchEnabled != flag)
	{
		m_bIsTouchEnabled = flag;
		if (flag){
			//三个参数含义分别为：1. 触摸事件接受对象；2.触摸事件优先级，值越小优先级越高；3.表明是否“吞噬”一个触摸
			CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
			
		}
		else{
			//关闭触摸事件removeDelegate（）
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			//dispatcher: n. 调度员；[计] 调度程序；[计] 分配器
			//delegate：vt. 委派…为代表	n.代表
		}
	}
}

bool TouchLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//当没有TouchLayer时this只能用于非静态成员函数内部
	this->getGameScene()->cannonAimAt(this->locationFromTouch(pTouch));
	return true;
}
void TouchLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	this->getGameScene()->cannonAimAt(this->locationFromTouch(pTouch));
}
void TouchLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	this->getGameScene()->cannonShootTo(this->locationFromTouch(pTouch));
}

CCPoint TouchLayer::locationFromTouch(cocos2d::CCTouch* pTouch)
{
	//把UI坐标系转换成为GL坐标系
	return CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}