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
	string ShowBattleField(Player Player, Monster Monster);

	bool IsValidDecision(string InValue, bool IsField);
};

