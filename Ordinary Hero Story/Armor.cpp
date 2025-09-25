#include "Armor.h"

Armor* Armor::Upgrade()
{
	SetUpgradeLevel(GetUpgradeLevel() + 1);
	SetDefencePoint(GetDefencePoint() + GetUpgradeLevel() * GetUpgradeValue());
	SetRequiredGoldToUpgrade(GetRequiredGoldForUpgrade() + GetUpgradeLevel() * 10);

	return this;
}
