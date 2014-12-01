#include "Cannon.h"
#include "StaticData.h"
USING_NS_CC;

void Cannon::setType(CannonType type)
{
	if (_type != type){
		if (type >= k_Cannon_Type_Count){
			type = k_Cannon_Type_1;
		}
		else if(type<k_Cannon_Type_1){
			type = (CannonType)(k_Cannon_Type_Count - 1); //??不知道“-1”意图是啥; 答：循环呗
		}
	
		//初次调用setType函数时，removeChildByTag所需要移除的节点不存在，但并不担心会内存泄露，因为引擎底部已经处理好了
		this->removeChildByTag(_type, false);
		CCSprite* newCannonSprite = (CCSprite*)_cannonSprites->objectAtIndex(type);
		this->addChild(newCannonSprite, 0, type);
		_type = type;
	}
}

Cannon* Cannon::create(CannonType type)
{
	Cannon* cannon = new Cannon();
	cannon->init(type);
	cannon->autorelease();
	return cannon;

}

bool Cannon::init(CannonType type)
{
	//创建大炮数量
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Type_Count);
	_cannonSprites->retain();

	//确定大炮的位置，anchor锚点
	CCPoint anchorPoints = CCPointMake(0.5,0.26);
	for (int i = k_Cannon_Type_1; i < k_Cannon_Type_Count; i++){
		//创建一个大炮
		CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("cannon_level_name_format"), i + 1);
		CCSprite* cannonSprite=CCSprite::createWithSpriteFrameName(fileName->getCString());
		cannonSprite->setAnchorPoint(anchorPoints);//把大炮放到这个位置
		_cannonSprites->addObject(cannonSprite);
	}
	this->setType(type);
	return true;
}

CCSprite* Cannon::getCurCannonSprite()
{
	return (CCSprite*)_cannonSprites->objectAtIndex(_type);
}

CannonType Cannon::getType()
{
	return _type;
}
//构造函数不需要返回值，所以只需如下即可
Cannon::Cannon()
{
	_type = (CannonType)k_Cannon_Type_Invalid;
}
//析构函数
Cannon::~Cannon()
{
	CC_SAFE_RELEASE(_cannonSprites);//释放“_cannonSprites”私有变量数组
}

//瞄准函数
void Cannon::aimAt(CCPoint target)
{
	//convertToWorldSpace()将节点坐标转换到屏幕坐标系中
	CCPoint location = this->getParent()->convertToWorldSpace(this->getPosition());
	//ccpAngleSigned（a,b）坐标运算函数，参数a，b分别是夹角两边的断点，而这两条边的焦点默认是CCPointZero,既坐标原点
	float angle = ccpAngleSigned(ccpSub(target,location),CCPointMake(0,1));
	//rotaion n. 旋转；循环，轮流
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}