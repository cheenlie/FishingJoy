#include "cocos2d.h"
USING_NS_CC;
//动画动作模拟
void func()
{
	const char* s_fishPath="";
	int numOfFishFrame=0;
	CCSprite* fish=CCSprite::create();
	
	//利用CCTextureCache加载鱼游动的“动画纹理”
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(s_fishPath);
	float w = texture->getContentSize().width/ numOfFishFrame;
	float h = texture->getContentSize().height;

	//创建“动画“对象
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.15f);
	//修改每帧播放的时间间隔为0.15秒
	//animation->setDelay(0.15f);
	for (int i = 0; i < numOfFishFrame; i++)
		//给“动画”添加每一帧所使用的”框帧“，框帧的纹理都一样。
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i*w, 0, w, h));
	//利用创建好的”动画“对象来创建一个”动画动作“
	CCAnimate* animate = CCAnimate::create(animation);
	//用鱼”精灵“来播放此动画
	fish->runAction(CCRepeatForever::create(animate));

	//总结：（1）动画动作：动画的播放器，使用动画对象创建，只能作用于精灵。
	//     （2）精灵->动画动作->动画（动画纹理）;用精灵来执行动画动作。
}


