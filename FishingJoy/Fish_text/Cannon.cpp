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
			type = (CannonType)(k_Cannon_Type_1 - 1); //??��֪����-1����ͼ��ɶ
		}
	
		//���ε���setType����ʱ��removeChildByTag����Ҫ�Ƴ��Ľڵ㲻���ڣ����������Ļ��ڴ�й¶����Ϊ����ײ��Ѿ��������
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
	//������������
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Type_Count);
	_cannonSprites->retain();

	//ȷ�����ڵ�λ�ã�anchorê��
	CCPoint anchorPoints = CCPointMake(0.5,0.26);
	for (int i = k_Cannon_Type_1; i < k_Cannon_Type_Count; i++){
		//����һ������
		CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("cannon_level_name_format"), i + 1);
		CCSprite* cannonSprite=CCSprite::createWithSpriteFrameName(fileName->getCString());
		cannonSprite->setAnchorPoint(anchorPoints);//�Ѵ��ڷŵ����λ��
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
//���캯������Ҫ����ֵ������ֻ�����¼���
Cannon::Cannon()
{
	_type = (CannonType)k_Cannon_Type_Invalid;
}
//��������
Cannon::~Cannon()
{
	CC_SAFE_RELEASE(_cannonSprites);//�ͷš�_cannonSprites��˽�б�������
}

//��׼����
void Cannon::aimAt(CCPoint target)
{
	//convertToWorldSpace()���ڵ�����ת������Ļ����ϵ��
	CCPoint location = this->getParent()->convertToWorldSpace(this->getPosition());
	//ccpAngleSigned��a,b���������㺯��������a��b�ֱ��Ǽн����ߵĶϵ㣬���������ߵĽ���Ĭ����CCPointZero,������ԭ��
	float angle = ccpAngleSigned(ccpSub(target,location),CCPointMake(0,1));
	//rotaion n. ��ת��ѭ��������
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}