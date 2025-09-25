#pragma once
#include "Monster.h"
#include "Fields.h"
#include "Player.h"

class MonsterManager
{
public:
	Monster* CreateMonster(Player Player, Field InCurrentField);
	Monster* CreateField1Monster(Player* Player);
	int GnerateLevel(int InMin, int InMax);
	int GnerateDropGold(int InMin, int InMax);
	int GnerateDropExp(int InMin, int InMax);
};

