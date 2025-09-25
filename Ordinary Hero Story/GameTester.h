#pragma once
#include "Player.h"
#include "PlayerManager.h"
#include "Stats.h"

class GameTester
{
public:
	void ShowPlayerStatus(Player* InPlayer);
	void ShowPlayerStatPoints(Player* InPlayer);
	void ShowPlayerWearingList(Player* InPlayer);
	void ShowPlayerArtifactList(Player* InPlayer);
	void SetStatTest(PlayerManager* InMainPlayerManager, Player* InPlayer, Stats InType, int InStat);
	void UpgradeTest(PlayerManager* InMainPlayerManager, Player* InPlayer, int InUpgradeCount);
};
