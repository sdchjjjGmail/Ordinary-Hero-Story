#include "Monster.h"

void Monster::Attack(ICanBattle* InTarget, int InDamage)
{
	InTarget->TakeDamage(InDamage);
}

void Monster::TakeDamage(int InDamage)
{
	SetHitPoint(GetHitPoint() - (InDamage - GetDefencePoint()));
}
