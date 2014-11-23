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

//����setTouchEnabled������������ʱ�򿪺͹رմ���
void TouchLayer::setTouchEnabled(bool flag)
{
	if (m_bIsTouchEnabled != flag)
	{
		m_bIsTouchEnabled = flag;
		if (flag){
			//������������ֱ�Ϊ��1. �����¼����ܶ���2.�����¼����ȼ���ֵԽС���ȼ�Խ�ߣ�3.�����Ƿ����ɡ�һ������
			CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
			
		}
		else{
			//�رմ����¼�removeDelegate����
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
			//dispatcher: n. ����Ա��[��] ���ȳ���[��] ������
			//delegate��vt. ί�ɡ�Ϊ����	n.����
		}
	}
}

bool TouchLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//��û��TouchLayerʱthisֻ�����ڷǾ�̬��Ա�����ڲ�
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
	//��UI����ϵת����ΪGL����ϵ
	return CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}