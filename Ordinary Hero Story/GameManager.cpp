#include "GameManager.h"
#include "GameTester.h"
#include <random>

void GameManager::GameStart()
{
	RunGame();

	//GameTester Tester;
	//Tester.UpgradeTest(&MainPlayerManager, MainPlayer, 3);
	//Tester.SetStatTest(&MainPlayerManager, MainPlayer, Stats::Speed, 5);
	//Tester.ShowPlayerStatus(MainPlayer);
	//Tester.ShowPlayerStatPoints(MainPlayer);
	//Tester.ShowPlayerWearingList(MainPlayer);
	//Tester.ShowPlayerArtifactList(MainPlayer);
}

void GameManager::RunGame()
{
	PlayerManager MainPlayerManager;
	MonsterManager MonsterManager;
	MapManager MapManager;
	MainPlayerManager.CreatePlayer();

	bool GameEnd = false;
	do
	{
		if (EnterVilage())
		{
			break;
		}
		if (EnterField())
		{
			break;
		}
	} while (!GameEnd);
}

bool GameManager::EnterVilage()
{
	printf("Enter Vilage\n");
	GameMapManager.SetCurrentMap(Field::Vilage);
	bool Out = false;
	bool GameEnd = false;
	while(!Out)
	{
		int Flag = stoi(GameUiManager.ShowVilageUi());

		switch (Flag)
		{
		case 1:
			printf("대장간 입장!\n");
			break;
		case 2:
			printf("물약 상점!\n");
			break;
		case 3:
			Out = true;
			break;
		case 4:
			Out = true;
			GameEnd = true;
			break;
		default:
			Out = true;
			break;
		}
	}
	return GameEnd;
}

bool GameManager::EnterField()
{
	GameMapManager.SetCurrentMap(Field::Field1);
	bool Out = false;
	bool GameEnd = false;

	while (!Out)
	{
		int Flag = 0;
		string sFlag = GameUiManager.ShowFieldUi();

		if (sFlag == "d" || sFlag == "D")
		{
			MoveForward();
			continue;
		}
		else
		{
			Flag = stoi(sFlag);
		}

		switch (Flag)
		{
		case 1:
			printf("스테이터스!\n");
			break;
		case 2:
			printf("장비창!\n");
			break;
		case 3:
			Out = true;
			break;
		case 4:
			Out = true;
			GameEnd = true;
			break;
		default:
			Out = true;
			break;
		}
	}
	return GameEnd;
}

void GameManager::MoveForward()
{
	printf("앞으로 이동!\n");
	if (EncounterMonster())
	{
		Monster* CreatedMonster = EncounterMonsterManager.CreateMonster(*MainPlayerManager.GetCurrentPlayer(), GameMapManager.GetCurrentMap());
		StartBattle(CreatedMonster);
	}
}

void GameManager::StartBattle(Monster* Monster)
{
	printf("전투 발생!\n");
	bool BattleFinish = false;
	int Flag = 0;
	
	printf("player attack point : %d\n", MainPlayerManager.GetCurrentPlayer()->GetAttackPoint());
	printf("player gold : %d\n", MainPlayerManager.GetCurrentPlayer()->GetMyGold());
	string sFlag = "";
	while (!BattleFinish)
	{
		if (Monster->GetHitPoint() <= 0)
		{
			printf("Victory!\n");
			MainPlayerManager.GetCurrentPlayer()->SetMyGold(Monster->GetDropGold());
			MainPlayerManager.GetCurrentPlayer()->SetExPoint(Monster->GetDropExp());
			delete Monster;
			Monster = nullptr;

			GameTester Tester;
			Tester.ShowPlayerStatus(MainPlayerManager.GetCurrentPlayer());
			Tester.ShowPlayerStatPoints(MainPlayerManager.GetCurrentPlayer());

			printf("\nPlayer Info\n");
			printf("Level : %d\n", MainPlayerManager.GetCurrentPlayer()->GetLevel());
			printf("HP : %d\n", MainPlayerManager.GetCurrentPlayer()->GetHitPoint());
			printf("AP : %d\n", MainPlayerManager.GetCurrentPlayer()->GetAttackPoint());
			printf("DP : %d\n", MainPlayerManager.GetCurrentPlayer()->GetDefencePoint());
			printf("SP : %d\n", MainPlayerManager.GetCurrentPlayer()->GetSpeed());
			printf("CC : %d\n", MainPlayerManager.GetCurrentPlayer()->GetCriticalChance());
			printf("CDR : %d\n", MainPlayerManager.GetCurrentPlayer()->GetCriticalDamageRate());
			printf("My Gold : %d\n", MainPlayerManager.GetCurrentPlayer()->GetMyGold());
			printf("Exp : %d/%d\n", MainPlayerManager.GetCurrentPlayer()->GetExp(), MainPlayerManager.GetCurrentPlayer()->GetRequiredExpForLvUp());
			break;
		}
		sFlag = GameUiManager.ShowBattleField(*MainPlayerManager.GetCurrentPlayer(), *Monster);
		Flag = stoi(sFlag);
		switch (Flag)
		{
		case 1:
			MainPlayerManager.GetCurrentPlayer()->Attack(Monster, MainPlayerManager.GetCurrentPlayer()->GetAttackPoint());
			break;
		case 2:
			BattleFinish = true;
			break;
		}
	}
}

bool GameManager::EncounterMonster()
{
	return PosibilityGenerator(50);
}

bool GameManager::PosibilityGenerator(int InPercentage)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 99);

	return dist(gen) < InPercentage;
}
