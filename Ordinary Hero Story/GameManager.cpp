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
			// �������ͽ� Ȯ��
			GameUiManager->ShowStatus(MainPlayerManager->GetCurrentPlayer());
			break;
		case 2:
			// ��������Ʈ Ȯ�� �� ���
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(MainPlayerManager->GetCurrentPlayer())));
			break;
		case 3:
			// ���尣 ���� �� ��� ��ȭ
			printf("���尣 ����!\n");
			break;
		case 4:
			// ���� ���� ���� �� ���� ����
			printf("���� ����!\n");
			break;
		case 5:
			// �ʵ�� �̵�
			Out = true;
			break;
		case 6:
			// ���� ����
			Out = true;
			GameEnd = true;
			break;
		default:
			// �� �� �Է� �Ұ�
			Out = true;
			break;
		}
	}
	return GameEnd;
}

bool GameManager::EnterField()
{
	printf("\n�ʵ忡 �����߽��ϴ�!\n");
	printf("d Ű�� �Է��Ͽ� ������ �̵��ϼ���.\n");
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
				printf("ĳ������ ü���� ��� ���������ϴ�.\n");
				printf("������ ü������ �������� ��Ȱ�մϴ�.\n");
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
			// �������ͽ� Ȯ��
			GameUiManager->ShowStatus(MainPlayerManager->GetCurrentPlayer());
			break;
		case 2:
			// ��� Ȯ��
			GameUiManager->ShowWearings(MainPlayerManager->GetCurrentPlayer());
			break;
		case 3:
			// ��������Ʈ Ȯ�� �� ���
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(MainPlayerManager->GetCurrentPlayer())));
			break;
		case 4:
			// ������ �̵�
			Out = true;
			break;
		case 5:
			// ���� ����
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
		printf("���� ���� �Է��� �ּ���(0 �Է� �� ���.) : ");
		cin >> Value;

		if (Value > MainPlayerManager->GetCurrentPlayer()->GetAvailableStat())
		{
			printf("������ �����մϴ�.\n");
			continue;
		}
		else if (Value < 0)
		{
			printf("�������� ���� �Է��� �ּ���.\n");
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
	printf("\n������ �̵�!\n");
	if (EncounterMonster())
	{
		printf("\n���Ϳ� �����ƽ��ϴ�!\n");
		Monster* CreatedMonster = EncounterMonsterManager->CreateMonster(*MainPlayerManager->GetCurrentPlayer(), GameMapManager->GetCurrentMap());
		StartBattle(CreatedMonster);
	}
}

void GameManager::StartBattle(Monster* InMonster)
{
	printf("���� ����\n");

	bool BattleFinish = false;
	int Turn = 1;
	GameTester Tester;

	while (!BattleFinish)
	{
		if (InMonster->GetHitPoint() <= 0)
		{
			printf("�¸�!!\n");
			printf("%d��ŭ�� ����ġ�� �����!\n", InMonster->GetDropExp());
			printf("%d��ŭ�� ��带 �����!\n", InMonster->GetDropGold());

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
			printf("�й�..");
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
	printf("���� ü�� : %d/%d\n", Me()->GetHitPoint(), Me()->GetFullHitPoint());
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
	printf("%s�� ����!", InMonster->GetName().c_str());
	InMonster->Attack(MainPlayerManager->GetCurrentPlayer(), CalculateMonsterDamage(InMonster));
}

int GameManager::CalculateDamage()
{
	// ũ��Ƽ�� ������ ��� GetAttackPoint() * GetCriticalDamageRate() ����
	// �Ϲ� ������ ��� GetAttackPoint() ����
	return IsCritical()
		? MainPlayerManager->GetCurrentPlayer()->GetAttackPoint()
		* MainPlayerManager->GetCurrentPlayer()->GetCriticalDamageRate()
		: MainPlayerManager->GetCurrentPlayer()->GetAttackPoint();
}

int GameManager::CalculateMonsterDamage(Monster* InMonster)
{
	// ũ��Ƽ�� ������ ��� GetAttackPoint() * GetCriticalDamageRate() ����
	// �Ϲ� ������ ��� GetAttackPoint() ����
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

// true or false Ȯ�� ����
bool GameManager::PosibilityGenerator(int InPercentage)
{
	// 0~99 ���� ���� �� �ۼ�Ƽ�� ������ ���� ��� true ����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 99);

	return dist(gen) < InPercentage;
}
