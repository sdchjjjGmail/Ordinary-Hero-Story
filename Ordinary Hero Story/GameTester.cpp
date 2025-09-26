#include "GameTester.h"

void GameTester::ShowPlayerStatus(Player* InPlayer)
{
	printf("\nPlayer Info\n");
	printf("Level : %d\n", InPlayer->GetLevel());
	printf("HP : %d\n", InPlayer->GetHitPoint());
	printf("AP : %d\n", InPlayer->GetAttackPoint());
	printf("DP : %d\n", InPlayer->GetDefencePoint());
	printf("SP : %d\n", InPlayer->GetSpeed());
	printf("CC : %d\n", InPlayer->GetCriticalChance());
	printf("CDR : %d\n", InPlayer->GetCriticalDamageRate());
	printf("My Gold : %d\n", InPlayer->GetMyGold());
	printf("Exp : %d/%d\n", InPlayer->GetExp(), InPlayer->GetRequiredExpForLvUp());
}

void GameTester::ShowPlayerStatPoints(Player* InPlayer)
{
	printf("\nPlayer Stat Points\n");
	printf("HP : %d\n", InPlayer->GetHitPointStat());
	printf("AP : %d\n", InPlayer->GetAttackPointStat());
	printf("DP : %d\n", InPlayer->GetDefencePointStat());
	printf("SP : %d\n", InPlayer->GetSpeedStat());
	printf("CC : %d\n", InPlayer->GetCriticalChanceStat());
	//printf("CDR : %d\n", InPlayer->GetCriticalDamageRateStat());
	printf("Stats : %d\n", InPlayer->GetAvailableStat());
}

void GameTester::ShowPlayerWearingList(Player* InPlayer)
{
	printf("\nWeapon Info\n");
	printf("Upgraded : %d\n", InPlayer->GetPlayerWeapon()->GetUpgradeLevel());
	printf("AP : %d\n", InPlayer->GetPlayerWeapon()->GetAttackPoint());
	printf("Gold For Upgrade : %d\n", InPlayer->GetPlayerWeapon()->GetRequiredGoldForUpgrade());

	printf("\nArmor Info\n");
	printf("Upgraded : %d\n", InPlayer->GetPlayerArmor()->GetUpgradeLevel());
	printf("DP : %d\n", InPlayer->GetPlayerArmor()->GetDefencePoint());
	printf("Gold For Upgrade : %d\n", InPlayer->GetPlayerArmor()->GetRequiredGoldForUpgrade());
}

void GameTester::ShowPlayerArtifactList(Player* InPlayer)
{
}

void GameTester::SetStatTest(PlayerManager* InMainPlayerManager, Player* InPlayer, Stats InType, int InStat)
{
	switch (InType)
	{
	case Stats::HitPoint:
		InPlayer->SetHitPointStat(InPlayer->GetHitPointStat() + InStat);
		InMainPlayerManager->SetPlayerHitPoint();
		break;
	case Stats::AttackPoint:
		InPlayer->SetAttackPointStat(InPlayer->GetAttackPointStat() + InStat);
		InMainPlayerManager->SetPlayerAttackPoint();
		break;
	case Stats::DefencePoint:
		InPlayer->SetDefencePointStat(InPlayer->GetDefencePointStat() + InStat);
		InMainPlayerManager->SetPlayerDefencePoint();
		break;
	case Stats::Speed:
		InPlayer->SetSpeedStat(InPlayer->GetSpeedStat() + InStat);
		InMainPlayerManager->SetPlayerSpeed();
		break;
	case Stats::CriticalChance:
		InPlayer->SetCriticalChanceStat(InPlayer->GetCriticalChanceStat() + InStat);
		InMainPlayerManager->SetPlayerCriticalChance();
		break;
	//case Stats::CriticalDamageRate:
	//	InPlayer->SetCriticalDamageRateStat(InPlayer->GetCriticalDamageRateStat() + InStat);
	//	InMainPlayerManager->SetPlayerCriticalDamageRate();
	//	break;
	default:
		break;
	}
}

void GameTester::UpgradeTest(PlayerManager* InMainPlayerManager, Player* InPlayer, int InUpgradeCount)
{
	for (int i = 0; i < InUpgradeCount; i++)
	{
		InMainPlayerManager->SetWeapon(InMainPlayerManager->GetWeapon()->Upgrade());
	}
	for (int i = 0; i < InUpgradeCount; i++)
	{
		InMainPlayerManager->SetArmor(InMainPlayerManager->GetArmor()->Upgrade());
	}
}


