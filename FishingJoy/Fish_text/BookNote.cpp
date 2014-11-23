#include "cocos2d.h"
USING_NS_CC;
//��������ģ��
void func()
{
	const char* s_fishPath="";
	int numOfFishFrame=0;
	CCSprite* fish=CCSprite::create();
	
	//����CCTextureCache�������ζ��ġ���������
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(s_fishPath);
	float w = texture->getContentSize().width/ numOfFishFrame;
	float h = texture->getContentSize().height;

	//����������������
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.15f);
	//�޸�ÿ֡���ŵ�ʱ����Ϊ0.15��
	//animation->setDelay(0.15f);
	for (int i = 0; i < numOfFishFrame; i++)
		//�������������ÿһ֡��ʹ�õġ���֡������֡������һ����
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i*w, 0, w, h));
	//���ô����õġ�����������������һ��������������
	CCAnimate* animate = CCAnimate::create(animation);
	//���㡱���顰�����Ŵ˶���
	fish->runAction(CCRepeatForever::create(animate));

	//�ܽ᣺��1�����������������Ĳ�������ʹ�ö������󴴽���ֻ�������ھ��顣
	//     ��2������->��������->��������������;�þ�����ִ�ж���������
}


