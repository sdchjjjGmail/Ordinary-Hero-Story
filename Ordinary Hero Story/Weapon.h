#pragma once
#include "Item.h"
#include "IUpgradable.h"

class Weapon : public Item, public IUpgradable
{
public:
	Weapon()
	{
		AttackPoint = 20;
		UpgradeLevel = 0;
		RequiredGoldForUpgrade = 0;
	} 
	virtual ~Weapon() {};

	virtual Weapon* Upgrade() override;

	int GetAttackPoint() const
	{
		return AttackPoint;
	}
	int GetUpgradeLevel()const
	{
		return UpgradeLevel;
	}
	int GetRequiredGoldForUpgrade()const
	{
		return RequiredGoldForUpgrade;
	}
	int GetUpgradeValue() const
	{
		return UpgradeValue;
	}

	void SetAttackPoint(int InAttackPoint)
	{
		AttackPoint = InAttackPoint;
	}
	void SetUpgradeLevel(int InUpgradeLevel)
	{
		UpgradeLevel = InUpgradeLevel;
	}
	void SetRequiredGoldToUpgrade(int InRequiredGoldToUpgrade)
	{
		RequiredGoldForUpgrade = InRequiredGoldToUpgrade;
	}

private:
	static constexpr int UpgradeValue = 10;

	int AttackPoint;
	int UpgradeLevel;
	int RequiredGoldForUpgrade;
};
