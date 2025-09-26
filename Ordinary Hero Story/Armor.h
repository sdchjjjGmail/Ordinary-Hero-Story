#pragma once
#include "IUpgradable.h"

class Armor : public IUpgradable
{
public:
	Armor()
	{
		DefencePoint = 10;
		UpgradeLevel = 0;
		RequiredGoldForUpgrade = 20;
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
	static constexpr int UpgradeValue = 5;
	int DefencePoint;
	int UpgradeLevel;
	int RequiredGoldForUpgrade;
};

