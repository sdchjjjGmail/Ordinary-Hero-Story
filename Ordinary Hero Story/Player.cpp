#include "Player.h"

void Player::Attack(ICanBattle* InTarget, int InDamage)
{
	InTarget->TakeDamage(InDamage);
}

void Player::TakeDamage(int InDamage)
{
	SetHitPoint(GetHitPoint() - (InDamage - GetDefencePoint()));
}
