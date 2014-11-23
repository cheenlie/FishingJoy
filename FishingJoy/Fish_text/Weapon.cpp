#include "Weapon.h"
#include "StaticData.h"
USING_NS_CC;

Weapon* Weapon::create(CannonType type )
{
	Weapon* weapon = new Weapon();
	weapon->init(type);
	weapon->autorelease();
	return weapon;
}

bool Weapon::init(CannonType type)
{
	_cannon = Cannon::create(type);
	this->addChild(_cannon);
	
	_bullet = Bullet::create();
	_bullet->setVisible(false);
	this->addChild(_bullet);

	_fishingNet = FishingNet::create();
	_fishingNet->setVisible(false);
	this->addChild(_fishingNet);

	return true;
}

bool Weapon::shootTo(CCPoint touchLocation)
{
	//若已经发射子弹，返回发射失败错误
	if (this->weaponStatus() != k_Weapon_Status_None){
		return false;
	}
	else{
		float distance = 180 * (_cannon->getType() + 1); //根据大炮类型确定子弹发射距离
		CCPoint normal = ccpNormalize(ccpSub(touchLocation,this->getParent()->convertToWorldSpace(this->getPosition())));
		//vector n. 矢量；带菌者；航线
		CCPoint vector = ccpMult(normal,distance);
		CCPoint target = ccpAdd(this->getPosition(),vector);
		_bullet->flyTo(target);
		return true;
	}
}

void Weapon::aimAt(CCPoint target)
{
	_cannon->aimAt(target);
}

int Weapon::weaponStatus()
{
	if (_bullet->isVisible()) //假如有子弹
	{
		return k_Weapon_Status_Bullet;
	}
	else if (_fishingNet->isVisible()){//假如有渔网
		return k_Weapon_Status_FishingNet;
	}
	return k_Weapon_Status_None;
	
}