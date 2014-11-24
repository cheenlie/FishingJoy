#ifndef __FishingJoy__Bullet__
#define __FishingJoy__Bullet__
#include "cocos2d.h"



class Bullet:public cocos2d::CCNode
{
public:
	CREATE_FUNC(Bullet);
	//void init();//ʱ����ͻᱨ�������ʽ�������bool;��û��init()����ʱ����û��init����,����CREATE_FUNC���庯��ʱ������init����
	bool init();

	//�ӵ�����
	void flyTo(cocos2d::CCPoint target);
	//ʹ�ӵ���������
	void end();

	cocos2d::CCPoint getCollisionPoint();

protected:
	cocos2d::CCSprite* _bulletSprite;

};

#endif