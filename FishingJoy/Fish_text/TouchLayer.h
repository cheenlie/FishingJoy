
#ifndef __FishingJoy__TouchLayer__
#define __FishingJoy__TouchLayer__
#include "cocos2d.h"

//#include "GameScene.h"   //������һ�䣬GameScene.h�С� TouchLayer* _touchLayer;������ᱨ���������£�
                           //error C4430: ȱ������˵���� - �ٶ�Ϊ int.ע��:  C++ ��֧��Ĭ�� int
						   //****�²⣺ͷ�ļ�����������⣿��   �������о�
USING_NS_CC;

class GameScene; //��ӵ�GameScene�У����û���е�36�У�GameScene* getGameScene();���ᱨ���������ϣ�C4430

class TouchLayer : public cocos2d::CCLayer
{
public:

	CREATE_FUNC(TouchLayer);
	bool init();

	//ֻ��ʵ�ֵ��㴥�������ֻ��ʵ��CCTargetedTouchDelegate���������д�����ʵ��CCTargetedTouchDelegate��������Ϊ�ص�������
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);//���õ��Ǵ�Ŀ��Ĵ����¼�
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);


	//����setTouchEnabled������������ʱ�򿪺͹رմ����� �ȿ������رմ����Ľӿ�
	void setTouchEnabled(bool flag);
protected:

	GameScene* getGameScene();
	cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch* touch);
};
#endif