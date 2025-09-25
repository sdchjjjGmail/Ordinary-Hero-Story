#include "PlayerManager.h"

void PlayerManager::CreatePlayer()
{
	Player* MainPlayer = new Player(1, 50);
	SetPlayer(*MainPlayer);
	SetWeapon(MainPlayer, new Weapon());
	SetArmor(MainPlayer, new Armor());
}

void PlayerManager::SetWeapon(Player* InPlayer, Weapon* InWeapon)
{
	InPlayer->SetPlayerWeapon(InWeapon);
	SetPlayerAttackPoint(InPlayer);
}

void PlayerManager::SetArmor(Player* InPlayer, Armor* InArmor)
{
	InPlayer->SetPlayerArmor(InArmor);
	SetPlayerDefencePoint(InPlayer);
}

void PlayerManager::AddArtifact(Player* InPlayer, Artifact InArtifact)
{
}

void PlayerManager::Attack(Player* InPlayer, Monster* InTarget)
{
	InPlayer->Attack(InTarget, InPlayer->GetAttackPoint());
}

void PlayerManager::SetPlayerStat(Player* InPlayer, Stats InType ,int InStat)
{
	switch(InType)
	{
	case Stats::HitPoint:
		InPlayer->SetHitPointStat(InPlayer->GetHitPointStat() + InStat);
		SetPlayerHitPoint(InPlayer);
		break;
	case Stats::AttackPoint:
		InPlayer->SetAttackPointStat(InPlayer->GetAttackPointStat() + InStat);
		SetPlayerAttackPoint(InPlayer);
		break;
	case Stats::DefencePoint:
		InPlayer->SetDefencePointStat(InPlayer->GetDefencePointStat() + InStat);
		SetPlayerDefencePoint(InPlayer);
		break;
	case Stats::Speed:
		InPlayer->SetSpeedStat(InPlayer->GetSpeedStat() + InStat);
		SetPlayerSpeed(InPlayer);
		break;
	case Stats::CriticalChance:
		InPlayer->SetCriticalChanceStat(InPlayer->GetCriticalChanceStat() + InStat);
		SetPlayerCriticalChance(InPlayer);
		break;
	case Stats::CriticalDamageRate:
		InPlayer->SetCriticalDamageRateStat(InPlayer->GetCriticalDamageRateStat() + InStat);
		SetPlayerCriticalDamageRate(InPlayer);
		break;
	default:
		break;
	}
}

void PlayerManager::SetPlayerHitPoint(Player* InPlayer)
{
	InPlayer->SetHitPoint(
		InPlayer->GetOrgAttackPoint()
		+ InPlayer->GetHitPointStat() * InPlayer->GetStatValue()
	);
}

void PlayerManager::SetPlayerAttackPoint(Player* InPlayer)
{
	InPlayer->SetAttackPoint(
		InPlayer->GetOrgAttackPoint()
		+ InPlayer->GetAttackPointStat() * InPlayer->GetStatValue()
		+ GetWeapon(InPlayer)->GetAttackPoint()
	);
}

void PlayerManager::SetPlayerDefencePoint(Player* InPlayer)
{
	InPlayer->SetDefencePoint(
		InPlayer->GetOrgDefencePoint()
		+ InPlayer->GetDefencePointStat() * InPlayer->GetStatValue()
		+ GetArmor(InPlayer)->GetDefencePoint()
	);
}

void PlayerManager::SetPlayerSpeed(Player* InPlayer)
{
	InPlayer->SetSpeed(
		InPlayer->GetSpeed()
		+ InPlayer->GetSpeedStat() * InPlayer->GetStatValue()
	);
}

void PlayerManager::SetPlayerCriticalChance(Player* InPlayer)
{
	InPlayer->SetCriticalChance(
		InPlayer->GetCriticalChance()
		+ InPlayer->GetCriticalChanceStat() * InPlayer->GetStatValue()
	);
}

void PlayerManager::SetPlayerCriticalDamageRate(Player* InPlayer)
{
	InPlayer->SetCriticalDamageRate(
		InPlayer->GetOrgCriticalDamageRate()
		+ InPlayer->GetCriticalDamageRateStat() * InPlayer->GetStatValue()
	);
}

Weapon* PlayerManager::GetWeapon(Player* InPlayer)
{
	return InPlayer->GetPlayerWeapon();
}

Armor* PlayerManager::GetArmor(Player* InPlayer)
{
	return InPlayer->GetPlayerArmor();
}

Artifact PlayerManager::GetArtifact(Player* InPlayer)
{
	return Artifact();
}
