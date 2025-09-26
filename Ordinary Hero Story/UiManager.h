#pragma once
#include <string>
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

using namespace std;

class UiManager
{
public:
	string ShowVilageUi(Player* InPlayer);
	string ShowFieldUi();
	string ShowBlackSmith(Weapon* InWeapon, Armor* InArmor);
	string ShowPotionMarket(Potion* InPotion);
	string ShowBattleField(Monster* Monster);
	void ShowMonsterStatus(Monster* Monster);
	void ShowStatus(Player* Player);
	string ShowStatPoints(Player* Player);
	void ShowWearings(Player* Player);

	bool IsValidDecision(string InValue, bool IsField);
};

