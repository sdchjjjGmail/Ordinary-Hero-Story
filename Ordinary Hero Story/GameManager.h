#pragma once
#include "UiManager.h"
#include "PlayerManager.h"
#include "MonsterManager.h"
#include "MapManager.h"
#include "Actor.h"
#include "Player.h"
#include "Monster.h"
#include "Potion.h"

class GameManager
{
public:
	GameManager() 
		: HealingPotion(new Potion()),
		MainPlayerManager(new PlayerManager()),
		EncounterMonsterManager(new MonsterManager()),
		GameUiManager(new UiManager()),
		GameMapManager(new MapManager())
	{
	};

	void GameStart();
	void RunGame();
	bool EnterVilage();
	void MoveToBlackSmith(int InChoice);
	void MoveToPotionMarket(int InChoice);
	bool EnterField(Field InField);
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
	void LevelUpEvent();
	void TakeArtifact(int InLevel);

	bool PosibilityGenerator(int InPercentage);

	void ShowEnding();

	// MainPlayerManager->GetCurrentPlayer()... 호출의 부담을 줄이기 위해 작성한 함수.
	Player* Me()
	{
		if (MainPlayerManager != nullptr && MainPlayerManager->GetCurrentPlayer() != nullptr)
		{
			return MainPlayerManager->GetCurrentPlayer();
		}
		else
		{
			// 게임 시작 직전 초기화를 진행하기에 else로 빠질 수 없음
			return new Player();
		}
	}
	Potion* HealingPotion;
	PlayerManager* MainPlayerManager;
	MonsterManager* EncounterMonsterManager;
	UiManager* GameUiManager;
	MapManager* GameMapManager;
};
