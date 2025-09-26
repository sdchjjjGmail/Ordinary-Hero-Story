#include "GameManager.h"
#include "GameTester.h"
#include <random>
#include <iostream>

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
	MainPlayerManager->SetPlayerWearings();

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
	GameMapManager->SetCurrentMap(Field::Vilage);
	bool Out = false;
	bool GameEnd = false;
	while(!Out)
	{
		int Flag = stoi(GameUiManager->ShowVilageUi());

		switch (Flag)
		{
		case 1:
			// 스테이터스 확인
			GameUiManager->ShowStatus(MainPlayerManager->GetCurrentPlayer());
			break;
		case 2:
			// 스탯포인트 확인 및 사용
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(MainPlayerManager->GetCurrentPlayer())));
			break;
		case 3:
			// 대장간 입장 및 장비 강화
			printf("대장간 입장!\n");
			break;
		case 4:
			// 물약 상점 입장 및 물약 구매
			printf("물약 상점!\n");
			break;
		case 5:
			// 필드로 이동
			Out = true;
			break;
		case 6:
			// 게임 종료
			Out = true;
			GameEnd = true;
			break;
		default:
			// 그 외 입력 불가
			Out = true;
			break;
		}
	}
	return GameEnd;
}

bool GameManager::EnterField()
{
	printf("\n필드에 입장했습니다!\n");
	printf("d 키를 입력하여 앞으로 이동하세요.\n");
	GameMapManager->SetCurrentMap(Field::Field1);
	bool Out = false;
	bool GameEnd = false;

	while (!Out)
	{
		int Flag = 0;
		string sFlag = GameUiManager->ShowFieldUi();
		if (sFlag == "d" || sFlag == "D")
		{
			MoveForward();
			if (Me()->GetHitPoint() <= 0)
			{
				printf("캐릭터의 체력이 모두 떨어졌습니다.\n");
				printf("절반의 체력으로 마을에서 부활합니다.\n");
				//Me()->
			}
			continue;
		}
		else
		{
			Flag = stoi(sFlag);
		}

		switch (Flag)
		{
		case 1:
			// 스테이터스 확인
			GameUiManager->ShowStatus(MainPlayerManager->GetCurrentPlayer());
			break;
		case 2:
			// 장비 확인
			GameUiManager->ShowWearings(MainPlayerManager->GetCurrentPlayer());
			break;
		case 3:
			// 스탯포인트 확인 및 사용
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(MainPlayerManager->GetCurrentPlayer())));
			break;
		case 4:
			// 마을로 이동
			Out = true;
			break;
		case 5:
			// 게임 종료
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

void GameManager::IncreaseStat(int InType)
{
	Stats StatType = Stats::HitPoint;
	switch (InType)
	{
	case 1:
		StatType = Stats::HitPoint;
		break;
	case 2:
		StatType = Stats::AttackPoint;
		break;
	case 3:
		StatType = Stats::DefencePoint;
		break;
	case 4:
		StatType = Stats::Speed;
		break;
	case 5:
		StatType = Stats::CriticalChance;
		break;
	//case 6:
	//	StatType = Stats::CriticalDamageRate;
	//	break;
	}
	int Value = 0;
	while (true)
	{
		printf("스탯 값을 입력해 주세요(0 입력 시 취소.) : ");
		cin >> Value;

		if (Value > MainPlayerManager->GetCurrentPlayer()->GetAvailableStat())
		{
			printf("스탯이 부족합니다.\n");
			continue;
		}
		else if (Value < 0)
		{
			printf("정상적인 값을 입력해 주세요.\n");
			continue;
		}
		MainPlayerManager->GetCurrentPlayer()->SetAvailableStat(
			MainPlayerManager->GetCurrentPlayer()->GetAvailableStat() - Value
		);
		MainPlayerManager->SetPlayerStat(StatType, Value);
		break;
	}
}

void GameManager::MoveForward()
{
	printf("\n앞으로 이동!\n");
	if (EncounterMonster())
	{
		printf("\n몬스터와 마주쳤습니다!\n");
		Monster* CreatedMonster = EncounterMonsterManager->CreateMonster(*MainPlayerManager->GetCurrentPlayer(), GameMapManager->GetCurrentMap());
		StartBattle(CreatedMonster);
	}
}

void GameManager::StartBattle(Monster* InMonster)
{
	printf("전투 시작\n");

	bool BattleFinish = false;
	int Turn = 1;
	GameTester Tester;

	while (!BattleFinish)
	{
		if (InMonster->GetHitPoint() <= 0)
		{
			printf("승리!!\n");
			printf("%d만큼의 경험치를 얻었다!\n", InMonster->GetDropExp());
			printf("%d만큼의 골드를 얻었다!\n", InMonster->GetDropGold());

			Me()->SetExPoint(InMonster->GetDropExp());
			Me()->SetMyGold(InMonster->GetDropGold());

			delete InMonster;
			InMonster = nullptr;

			//Tester.ShowPlayerStatus(Me());
			//Tester.ShowPlayerStatPoints(Me());
			break;
		}
		else if (Me()->GetHitPoint() <= 0)
		{
			printf("패배..");
			break;
		}

		if (TurnCalculator(InMonster, Turn) == 1)
		{
			BattleFinish = PlayerTurn(InMonster);
			MonsterTurn(InMonster);
		}
		else 
		{
			MonsterTurn(InMonster);
			BattleFinish = PlayerTurn(InMonster);
		}
		Turn++;
	}
}

int GameManager::TurnCalculator(Monster* InMonster, int InTurn)
{
	int PlayerSpeed = Me()->GetSpeed() * InTurn;
	int MonsterSpeed = InMonster->GetSpeed() * InTurn;
	if (PlayerSpeed == MonsterSpeed)
	{
		return 1;
	}
	if (PlayerSpeed > 100)
	{
		PlayerSpeed -= 100;
	}
	if (MonsterSpeed > 100)
	{
		MonsterSpeed -= 100;
	}
	printf("PlayerSpeed : %d, MonsterSpeed : %d\n", PlayerSpeed, MonsterSpeed);
	if (PlayerSpeed > MonsterSpeed)
	{
		return 1;
	}
	return 2;
}

bool GameManager::PlayerTurn(Monster* InMonster)
{
	printf("현재 체력 : %d/%d\n", Me()->GetHitPoint(), Me()->GetFullHitPoint());
	int Flag = 0;
	string sFlag = "";
	sFlag = GameUiManager->ShowBattleField(*InMonster);
	Flag = stoi(sFlag);
	switch (Flag)
	{
	case 1:
		MainPlayerManager->GetCurrentPlayer()->Attack(InMonster, CalculateDamage());
		break;
	case 2:
		return true;
		break;
	}
	return false;
}

void GameManager::MonsterTurn(Monster* InMonster)
{
	printf("%s의 공격!", InMonster->GetName().c_str());
	InMonster->Attack(MainPlayerManager->GetCurrentPlayer(), CalculateMonsterDamage(InMonster));
}

int GameManager::CalculateDamage()
{
	// 크리티컬 공격일 경우 GetAttackPoint() * GetCriticalDamageRate() 리턴
	// 일반 공격일 경우 GetAttackPoint() 리턴
	return IsCritical()
		? MainPlayerManager->GetCurrentPlayer()->GetAttackPoint()
		* MainPlayerManager->GetCurrentPlayer()->GetCriticalDamageRate()
		: MainPlayerManager->GetCurrentPlayer()->GetAttackPoint();
}

int GameManager::CalculateMonsterDamage(Monster* InMonster)
{
	// 크리티컬 공격일 경우 GetAttackPoint() * GetCriticalDamageRate() 리턴
	// 일반 공격일 경우 GetAttackPoint() 리턴
	return IsMonsterCritical(InMonster)
		? InMonster->GetAttackPoint()
		* InMonster->GetCriticalDamageRate()
		: InMonster->GetAttackPoint();
}

bool GameManager::IsCritical()
{
	if (PosibilityGenerator(MainPlayerManager->GetCurrentPlayer()->GetCriticalChance()))
	{
		printf("Critical Hit!!\n");
		return true;
	}
	return false;
}

bool GameManager::IsMonsterCritical(Monster* InMonster)
{
	if (PosibilityGenerator(InMonster->GetCriticalChance()))
	{
		printf("Critical Hit!!\n");
		return true;
	}
	return false;
}

bool GameManager::EncounterMonster()
{
	return PosibilityGenerator(50);
}

// true or false 확률 계산기
bool GameManager::PosibilityGenerator(int InPercentage)
{
	// 0~99 난수 생성 후 퍼센티지 값보다 낮을 경우 true 리턴
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 99);

	return dist(gen) < InPercentage;
}
