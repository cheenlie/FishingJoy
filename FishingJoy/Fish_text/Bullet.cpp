#include "Bullet.h"
#include "StaticData.h"
USING_NS_CC;
enum{
	k_Bullet_Action = 0
};

bool Bullet::init()
{
	_bulletSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("bullet"));
	_bulletSprite->setAnchorPoint(CCPointMake(0.5,1.0));
	this->addChild(_bulletSprite);
	return true;

}

void Bullet::flyTo(CCPoint targetInWorldSpace)
{
	//�ӵ���ʼ��ɵ�
	CCPoint startInNodeSpace = CCPointZero;
	//�ѽڵ�����ת������Ļ������
	CCPoint startInWorldSpace = this->getParent()->convertToWorldSpace(startInNodeSpace);
	CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWorldSpace);
	//coordinate n. ����; radian,n. [��] ����;rotation ,n. ��ת.
	
	float angle = ccpAngleSigned(ccpSub(targetInWorldSpace,startInWorldSpace),CCPointMake(0,1));

	this->setRotation(CC_RADIANS_TO_DEGREES(angle));  //������ת�Ƕ�
	this->setPosition(startInNodeSpace);//ȷ���ӵ���ʼλ��
	this->setVisible(true);//���ӵ��ɼ�

	float speed = ccpDistance(startInNodeSpace,targetInNodeSpace)/300.0f;
	CCMoveTo* moveTo = CCMoveTo::create(speed,targetInNodeSpace);  //��speed�ٶ���������·������

	//callfunc_selector����һ���ص�������**�ص�����ֻ��Ҫ��һ�����������ɣ�����Ҫ���š�
	CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(Bullet::end));

	CCFiniteTimeAction* seq = CCSequence::create(moveTo, callFunc, NULL);  //�ӵ����г���һ�����޵�ʱ��
	seq->setTag(k_Bullet_Action);  //�����ӵ�״̬

	this->runAction(seq);// �ӵ�������



}
void Bullet::end()
{
	this->stopActionByTag(k_Bullet_Action);
	//�ӵ��ﵽָ�����������
	this->setVisible(false);
}