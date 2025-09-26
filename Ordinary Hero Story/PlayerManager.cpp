#include "PlayerManager.h"

void PlayerManager::SetPlayerWearings()
{
	SetWeapon(new Weapon());
	SetArmor(new Armor());
}

void PlayerManager::SetWeapon(Weapon* InWeapon)
{
	GetCurrentPlayer()->SetPlayerWeapon(InWeapon);
	SetPlayerAttackPoint();
}

void PlayerManager::SetArmor(Armor* InArmor)
{
	GetCurrentPlayer()->SetPlayerArmor(InArmor);
	SetPlayerDefencePoint();
}

void PlayerManager::AddArtifact(Artifact InArtifact)
{
}

void PlayerManager::Attack(Monster* InTarget)
{
	GetCurrentPlayer()->Attack(InTarget, GetCurrentPlayer()->GetAttackPoint());
}

void PlayerManager::SetPlayerStat(Stats InType ,int InStat)
{
	switch(InType)
	{
	case Stats::HitPoint:
		GetCurrentPlayer()->SetHitPointStat(GetCurrentPlayer()->GetHitPointStat() + InStat);
		SetPlayerHitPoint();
		break;
	case Stats::AttackPoint:
		GetCurrentPlayer()->SetAttackPointStat(GetCurrentPlayer()->GetAttackPointStat() + InStat);
		SetPlayerAttackPoint();
		break;
	case Stats::DefencePoint:
		GetCurrentPlayer()->SetDefencePointStat(GetCurrentPlayer()->GetDefencePointStat() + InStat);
		SetPlayerDefencePoint();
		break;
	case Stats::Speed:
		GetCurrentPlayer()->SetSpeedStat(GetCurrentPlayer()->GetSpeedStat() + InStat);
		SetPlayerSpeed();
		break;
	case Stats::CriticalChance:
		GetCurrentPlayer()->SetCriticalChanceStat(GetCurrentPlayer()->GetCriticalChanceStat() + InStat);
		SetPlayerCriticalChance();
		break;
	//case Stats::CriticalDamageRate:
	//	GetCurrentPlayer()->SetCriticalDamageRateStat(GetCurrentPlayer()->GetCriticalDamageRateStat() + InStat);
	//	SetPlayerCriticalDamageRate();
	//	break;
	default:
		break;
	}
}

void PlayerManager::SetPlayerHitPoint()
{
	GetCurrentPlayer()->SetHitPoint(
		GetCurrentPlayer()->GetOrgHitPoint()
		+ GetCurrentPlayer()->GetHitPointStat() * GetCurrentPlayer()->GetStatValue()
	);
	GetCurrentPlayer()->SetFullHitPoint(
		GetCurrentPlayer()->GetOrgHitPoint()
		+ GetCurrentPlayer()->GetHitPointStat() * GetCurrentPlayer()->GetStatValue()
	);
}

void PlayerManager::SetPlayerAttackPoint()
{
	GetCurrentPlayer()->SetAttackPoint(
		GetCurrentPlayer()->GetOrgAttackPoint()
		+ GetCurrentPlayer()->GetAttackPointStat() * GetCurrentPlayer()->GetStatValue()
		+ GetWeapon()->GetAttackPoint()
	);
}

void PlayerManager::SetPlayerDefencePoint()
{
	GetCurrentPlayer()->SetDefencePoint(
		GetCurrentPlayer()->GetOrgDefencePoint()
		+ GetCurrentPlayer()->GetDefencePointStat() * GetCurrentPlayer()->GetStatValue()
		+ GetArmor()->GetDefencePoint()
	);
}

void PlayerManager::SetPlayerSpeed()
{
	GetCurrentPlayer()->SetSpeed(
		GetCurrentPlayer()->GetSpeed()
		+ GetCurrentPlayer()->GetSpeedStat() * GetCurrentPlayer()->GetStatValue()
	);
}

void PlayerManager::SetPlayerCriticalChance()
{
	GetCurrentPlayer()->SetCriticalChance(
		GetCurrentPlayer()->GetCriticalChance()
		+ GetCurrentPlayer()->GetCriticalChanceStat() * GetCurrentPlayer()->GetStatValue()
	);
}

void PlayerManager::UsePotion(Potion* InPotion)
{
	if (GetCurrentPlayer()->GetPotionCount() <= 0)
	{
		printf("포션이 부족합니다..\n");
	}
	else
	{
		printf("%d의 체력을 회복합니다.\n", InPotion->GetHealAmount());
		if (GetCurrentPlayer()->GetHitPoint() + InPotion->GetHealAmount() > GetCurrentPlayer()->GetFullHitPoint())
		{
			GetCurrentPlayer()->SetHitPoint(GetCurrentPlayer()->GetFullHitPoint());
		}
		else
		{
			GetCurrentPlayer()->SetHitPoint(
				GetCurrentPlayer()->GetHitPoint() + InPotion->GetHealAmount());
		}
		GetCurrentPlayer()->SetPotionCount(GetCurrentPlayer()->GetPotionCount() - 1);
	}
}

//void PlayerManager::SetPlayerCriticalDamageRate()
//{
//	GetCurrentPlayer()->SetCriticalDamageRate(
//		GetCurrentPlayer()->GetOrgCriticalDamageRate()
//		+ GetCurrentPlayer()->GetCriticalDamageRateStat() * GetCurrentPlayer()->GetStatValue()
//	);
//}

Weapon* PlayerManager::GetWeapon()
{
	return GetCurrentPlayer()->GetPlayerWeapon();
}

Armor* PlayerManager::GetArmor()
{
	return GetCurrentPlayer()->GetPlayerArmor();
}

Artifact PlayerManager::GetArtifact()
{
	return Artifact();
}
