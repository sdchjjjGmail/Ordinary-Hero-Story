#include "Weapon.h"

Weapon* Weapon::Upgrade()
{
	SetUpgradeLevel(GetUpgradeLevel() + 1);
	SetAttackPoint(GetAttackPoint() + GetUpgradeLevel() * GetUpgradeValue());
	SetRequiredGoldToUpgrade(GetRequiredGoldForUpgrade() + GetUpgradeLevel() * 10);

	return this;
}
