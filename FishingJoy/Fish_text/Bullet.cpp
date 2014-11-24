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
	//子弹开始起飞点
	CCPoint startInNodeSpace = CCPointZero;
	//把节点坐标转换到屏幕坐标中
	CCPoint startInWorldSpace = this->getParent()->convertToWorldSpace(startInNodeSpace);
	CCPoint targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWorldSpace);
	//coordinate n. 坐标; radian,n. [数] 弧度;rotation ,n. 旋转.
	
	float angle = ccpAngleSigned(ccpSub(targetInWorldSpace,startInWorldSpace),CCPointMake(0,1));

	this->setRotation(CC_RADIANS_TO_DEGREES(angle));  //设置旋转角度
	this->setPosition(startInNodeSpace);//确定子弹初始位置
	this->setVisible(true);//让子弹可见

	float speed = ccpDistance(startInNodeSpace,targetInNodeSpace)/300.0f;
	CCMoveTo* moveTo = CCMoveTo::create(speed,targetInNodeSpace);  //以speed速度沿着任务路径飞行

	//callfunc_selector创建一个回调函数【**回调函数只需要有一个函数名即可，不需要括号】
	CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(Bullet::end));

	CCFiniteTimeAction* seq = CCSequence::create(moveTo, callFunc, NULL);  //子弹飞行持续一个有限的时间
	seq->setTag(k_Bullet_Action);  //设置子弹状态

	this->runAction(seq);// 子弹飞起来



}
void Bullet::end()
{
	this->stopActionByTag(k_Bullet_Action);
	//子弹达到指定距离后隐藏
	this->setVisible(false);
}