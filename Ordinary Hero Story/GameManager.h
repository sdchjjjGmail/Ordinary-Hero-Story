#pragma once
#include "UiManager.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "MapManager.h"
#include "Player.h"
#include "Monster.h"

class GameManager
{
public:
	GameManager(PlayerManager InPlayerManager,
		MonsterManager InMonsterManager,
		UiManager InUiManager,
		MapManager InMapManager)
		: MainPlayerManager(InPlayerManager),
		EncounterMonsterManager(InMonsterManager),
		GameUiManager(InUiManager),
		GameMapManager(InMapManager) {};
	
	void GameStart();
	void RunGame();
	bool EnterVilage();
	bool EnterField();
	void MoveForward();
	bool EncounterMonster();
	void StartBattle(Monster* Monster);

	bool PosibilityGenerator(int InPercentage);

	PlayerManager MainPlayerManager;
	MonsterManager EncounterMonsterManager;
	UiManager GameUiManager;
	MapManager GameMapManager;
};
