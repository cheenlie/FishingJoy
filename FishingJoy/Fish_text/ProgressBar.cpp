#include "ProgressBar.h"
#include "ProgressProtocol.h"
USING_NS_CC;

enum{
	k_Progress_Action=0
};

//进度条运行
void ProgressBar::progressTo(float destination)
{
	float delta = destination - this->getPercentage();
	this->progressBy(delta);
}
void ProgressBar::progressBy(float delta)
{
	float maxPercentage = 100.0f;
	bool isFinished = false;
	float nextPercentage = delta + this->getPercentage();
	if (nextPercentage >= maxPercentage)
	{
		nextPercentage = maxPercentage;
		isFinished = true;
	}
	this->stopActionByTag(k_Progress_Action);
	//创建一个容量为2的数组
	CCArray* actions = CCArray::createWithCapacity(2);

	float duration = delta / this->getSpeed();
	CCProgressTo* to = CCProgressTo::create(duration, nextPercentage);

	actions->addObject(to);
	if (isFinished)
	{
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ProgressBar::loadingFinished));
		actions->addObject(callFunc);
	}
	//定义一个持续时间的运动
	CCFiniteTimeAction* seq = CCSequence::create(actions);
	//设置一个更新进度数字的回调函数
	CCCallFunc* updatePercentage = CCCallFunc::create(this, callfunc_selector(ProgressBar::updatePercentage));
	updatePercentage->setDuration(duration);

	//??question ，这个spwan是用来干嘛的？
	CCSpawn* spawn = CCSpawn::createWithTwoActions(seq,updatePercentage);
	spawn->setTag(k_Progress_Action);

	this->runAction(spawn);
}

void ProgressBar::loadingFinished()
{
	_target->loadingFinished();
}

//空格符号可能出错，如"　"和" "就不一样，前者为中文空格，后者为英文空格
ProgressBar* ProgressBar::create(ProgressDelegate* target, CCSprite *sprite)
{
	ProgressBar* progress = new ProgressBar();
	progress->init(target,sprite);
	progress->autorelease();
	return progress;
}

bool ProgressBar::init(ProgressDelegate* target, CCSprite* sprite)
{
	CCProgressTimer::initWithSprite(sprite);// CCProgressTimer is the subclass of CCNode
	this->setTarget(target);
	this->setMidpoint(CCPointMake(0,0.5));//定义进程开始位置
	this->setType(kCCProgressTimerTypeBar);//采用”条状“进度条形式，而没有采取”放射状“进度条
	this->setSpeed(1.0f);
	this->setBarChangeRate(CCPointMake(1,0));
	return true;
}

void ProgressBar::setBackground(CCNode* bg)
{
	this->removeChild(_background,true); //设置背景前都移除以前的背景
	_background = bg;
	CCSize size = this->getSprite()->getContentSize(); //获取当前精灵（精度条）的大小
	_background->setPosition(CCPointMake(size.width*0.5,size.height*0.5));
	this->addChild(_background, -1);//把背景层放在-1处，表示最深一层，保证不覆盖其他层
}

CCNode* ProgressBar::getBackground()
{
	return _background;
}

//原理和setBackground一样，只是放的z-order不一样
void ProgressBar::setForeground(CCNode* fg)
{
	this->removeChild(_foreground, true);
	_foreground = fg;
	CCSize size = this->getSprite()->getContentSize();
	_foreground->setPosition(CCPointMake(size.width*0.5, size.height*0.5));
	this->addChild(_foreground, 1);
}

CCNode* ProgressBar::getForeground()
{
	return _foreground;
}

void ProgressBar::updatePercentage()
{
	_target->progressPercentageSetter(this->getPercentage());
}