#pragma once
#include "UiManager.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "MapManager.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"

class GameManager
{
public:
	GameManager() 
		: MainPlayerManager(new PlayerManager()),
		EncounterMonsterManager(new MonsterManager()),
		GameUiManager(new UiManager()),
		GameMapManager(new MapManager())
	{
	};

	void GameStart();
	void RunGame();
	bool EnterVilage();
	bool EnterField();
	void IncreaseStat(int InType);
	void MoveForward();
	bool EncounterMonster();
	void StartBattle(Monster* InMonster);
	int TurnCalculator(Monster* InMonster, int InTurn);
	bool PlayerTurn(Monster* InMonster);
	void MonsterTurn(Monster* InMonster);
	int CalculateDamage();
	int CalculateMonsterDamage(Monster* InMonster);
	bool IsCritical();
	bool IsMonsterCritical(Monster* InMonster);

	bool PosibilityGenerator(int InPercentage);

	Player* Me()
	{
		if (MainPlayerManager != nullptr && MainPlayerManager->GetCurrentPlayer() != nullptr)
		{
			return MainPlayerManager->GetCurrentPlayer();
		}
		else
		{
			// ���� ���� ���� �ʱ�ȭ�� ���� �ϱ⿡ else�� ���� �� ����
			return new Player();
		}
	}

	PlayerManager* MainPlayerManager;
	MonsterManager* EncounterMonsterManager;
	UiManager* GameUiManager;
	MapManager* GameMapManager;
};
