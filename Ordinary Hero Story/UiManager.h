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
	string ShowBattleField(Player* InPlayer, Monster* InMonster);
	void ShowMonsterStatus(Monster* InMonster);
	void ShowStatus(Player* InPlayer);
	string ShowStatPoints(Player* InPlayer);
	void ShowWearings(Player* InPlayer, Potion* InPotion);
	void ShowEnding(Player* InPlayer);

	bool IsValidDecision(string InValue, bool IsField);
};

