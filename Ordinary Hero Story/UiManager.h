#pragma once
#include <string>
#include "Player.h"
#include "Monster.h"

using namespace std;

class UiManager
{
public:
	string ShowVilageUi();
	string ShowFieldUi();
	string ShowBlackSmith();
	string ShowPotionMarket();
	string ShowBattleField(Monster* Monster);
	void ShowMonsterStatus(Monster* Monster);
	void ShowStatus(Player* Player);
	string ShowStatPoints(Player* Player);
	void ShowWearings(Player* Player);

	bool IsValidDecision(string InValue, bool IsField);
};

