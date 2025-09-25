#pragma once
#include "Item.h"
#include "IUpgradable.h"

class Armor : public Item, public IUpgradable
{
public:
	Armor()
	{
		DefencePoint = 10;
		UpgradeLevel = 0;
		RequiredGoldForUpgrade = 0;
	}
	virtual ~Armor() {};

	virtual Armor* Upgrade() override;

	int GetDefencePoint() const
	{
		return DefencePoint;
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

	void SetDefencePoint(int InDefencePoint)
	{
		DefencePoint = InDefencePoint;
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
	static constexpr int UpgradeValue = 4;
	int DefencePoint;
	int UpgradeLevel;
	int RequiredGoldForUpgrade;
};

