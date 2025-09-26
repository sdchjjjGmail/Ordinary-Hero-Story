#include "GameManager.h"
#include "GameTester.h"
#include <random>
#include <iostream>

void GameManager::GameStart()
{
	RunGame();
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
		if (EnterField(GameMapManager->GetCurrentMap()))
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
		int Flag = stoi(GameUiManager->ShowVilageUi(Me()));

		switch (Flag)
		{
		case 1:
			// �������ͽ� Ȯ��
			GameUiManager->ShowStatus(Me());
			break;
		case 2:
			// ��������Ʈ Ȯ�� �� ���
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(Me())));
			break;
		case 3:
			// ��� Ȯ��
			GameUiManager->ShowWearings(Me(), HealingPotion);
			break;
		case 4:
			// ���尣 ���� �� ��� ��ȭ
			MoveToBlackSmith(stoi(GameUiManager->ShowBlackSmith(
				Me()->GetPlayerWeapon(), Me()->GetPlayerArmor())));
			break;
		case 5:
			// ���� ���� ���� �� ���� ����
			MoveToPotionMarket(stoi(GameUiManager->ShowPotionMarket(HealingPotion)));
			break;
		case 6:
			// �ʵ�� �̵�
			GameMapManager->SetCurrentMap(Field::Field1);
			Out = true;
			break;
		case 7:
			// �ʵ�� �̵�
			GameMapManager->SetCurrentMap(Field::Field2);
			Out = true;
			break;
		case 8:
			// �ʵ�� �̵�
			GameMapManager->SetCurrentMap(Field::Field3);
			Out = true;
			break;
		case 9:
			// ������ �̵�
			GameMapManager->SetCurrentMap(Field::BossField);
			Out = true;
			break;
		case 0:
			// ���� ����
			Out = true;
			GameEnd = true;
			break;
		case 157:
			// �׽�Ʈ�� ġƮ ��� �÷���
			GameTester Tester;
			Tester.SetCheat(Me());
			break;
		default:
			// �� �� �Է� �Ұ�
			Out = true;
			break;
		}
	}
	return GameEnd;
}

void GameManager::MoveToBlackSmith(int InChoice)
{
	if (InChoice == 1)
	{
		if (Me()->GetMyGold() < Me()->GetPlayerWeapon()->GetRequiredGoldForUpgrade())
		{
			printf("��尡 �����մϴ�!");
			return;
		}
		Me()->SetMyGold(
			Me()->GetMyGold()
			- Me()->GetPlayerWeapon()->GetRequiredGoldForUpgrade()
		);
		
		Me()->GetPlayerWeapon()->Upgrade();
		MainPlayerManager->SetWeapon(Me()->GetPlayerWeapon());
	}

	if (InChoice == 2)
	{
		if (Me()->GetMyGold() < Me()->GetPlayerArmor()->GetRequiredGoldForUpgrade())
		{
			printf("��尡 �����մϴ�!");
			return;
		}
		Me()->SetMyGold(
			Me()->GetMyGold()
			- Me()->GetPlayerArmor()->GetRequiredGoldForUpgrade()
		);

		Me()->GetPlayerArmor()->Upgrade();
		MainPlayerManager->SetArmor(Me()->GetPlayerArmor());
	}
}

void GameManager::MoveToPotionMarket(int InChoice)
{
	int Amount = 0;
	if (InChoice == 1)
	{
		printf("������ ���� �Է��ϼ���.\n");
		cin >> Amount;
		if (Amount < 0)
		{
			printf("�������� ���� �Է��ϼ���.\n");
		}
		else if (HealingPotion->GetPrice() * Amount > Me()->GetMyGold())
		{
			printf("��尡 �����մϴ�..\n");
		}
		else 
		{
			Me()->SetMyGold(Me()->GetMyGold() - HealingPotion->GetPrice() * Amount);
			Me()->SetPotionCount(Amount);
		}
	}
}

bool GameManager::EnterField(Field InField)
{
	printf("\n�ʵ忡 �����߽��ϴ�!\n");
	printf("d Ű�� �Է��Ͽ� ������ �̵��ϼ���.\n");

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
				Me()->SetHitPoint(Me()->GetFullHitPoint() / 2);
				EnterVilage();
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
			GameUiManager->ShowStatus(Me());
			break;
		case 2:
			// ��� Ȯ��
			GameUiManager->ShowWearings(Me(), HealingPotion);
			break;
		case 3:
			// ��������Ʈ Ȯ�� �� ���
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(Me())));
			break;
		case 4:
			// ���� ���
			if (Me()->GetHitPoint() == Me()->GetFullHitPoint())
			{
				printf("ü���� ���� ���ֽ��ϴ�.\n");
				break;
			}
			MainPlayerManager->UsePotion(HealingPotion);
			break;
		case 5:
			// ������ �̵�
			Out = true;
			break;
		case 0:
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
	if (InType == 0)
	{
		return;
	}
	if (InType < 0 || InType > 5)
	{
		printf("\n��ȿ���� ���� ���� �����Դϴ�.\n\n");
		return;
	}
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

		if (Value > Me()->GetAvailableStat())
		{
			printf("������ �����մϴ�.\n");
			continue;
		}
		else if (Value < 0)
		{
			printf("�������� ���� �Է��� �ּ���.\n");
			continue;
		}
		Me()->SetAvailableStat(
			Me()->GetAvailableStat() - Value
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
		Monster* CreatedMonster = EncounterMonsterManager->CreateMonster(Me(), GameMapManager->GetCurrentMap());
		StartBattle(CreatedMonster);
	}
}

void GameManager::StartBattle(Monster* InMonster)
{
	printf("���� ����\n");
	GameUiManager->ShowMonsterStatus(InMonster);
	bool BattleFinish = false;
	int Turn = 1;
	GameTester Tester;

	while (!BattleFinish)
	{
		if (InMonster->GetHitPoint() <= 0)
		{
			printf("\n�¸�!!\n");

			printf("%d��ŭ�� ����ġ�� �����!\n", InMonster->GetDropExp());
			printf("%d��ŭ�� ��带 �����!\n", InMonster->GetDropGold());

			Me()->SetExPoint(InMonster->GetDropExp());
			if (Me()->GetExp() >= Me()->GetRequiredExpForLvUp())
			{
				LevelUpEvent();
			}
			Me()->SetMyGold(Me()->GetMyGold() + InMonster->GetDropGold());

			delete InMonster;
			InMonster = nullptr;

			if (GameMapManager->GetCurrentMap() == Field::BossField)
			{
				ShowEnding();
			}

			break;
		}

		if (Me()->GetHitPoint() <= 0)
		{
			delete InMonster;
			InMonster = nullptr;

			printf("�й�..\n");
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
	int PlayerSpeed = Me()->GetSpeed();
	int MonsterSpeed = InMonster->GetSpeed();
	// �ӵ��� ������ ��� �÷��̾� ����
	if (PlayerSpeed == MonsterSpeed)
	{
		return 1;
	}
	
	printf("\nPlayerSpeed : %d, MonsterSpeed : %d\n", PlayerSpeed, MonsterSpeed);
	if (PlayerSpeed > MonsterSpeed)
	{
		if (InTurn % 3 == 0)
		{
			// ���� 3�� ����� ��� �ӵ��� ���� ���� ����
			return 2;
		}
		return 1;
	}
	else
	{
		if (InTurn % 3 == 0)
		{
			// ���� 3�� ����� ��� �ӵ��� ���� ���� ����
			return 1;
		}
		return 2;
	}
	
}

bool GameManager::PlayerTurn(Monster* InMonster)
{
	
	int Flag = 0;
	string sFlag = "";
	sFlag = GameUiManager->ShowBattleField(Me(), InMonster);
	Flag = stoi(sFlag);
	if (Flag >= 3 || Flag <= 0)
	{
		Flag = 1;
	}
	switch (Flag)
	{
	case 1:
		Me()->Attack(InMonster, CalculateDamage());
		break;
	case 2:
		delete InMonster;
		InMonster = nullptr;
		return true;
		break;
	}
	return false;
}

void GameManager::MonsterTurn(Monster* InMonster)
{
	printf("\n%s�� ����!\n", InMonster->GetName().c_str());
	InMonster->Attack(Me(), CalculateMonsterDamage(InMonster));
}

int GameManager::CalculateDamage()
{
	// ũ��Ƽ�� ������ ��� GetAttackPoint() * GetCriticalDamageRate() ����
	// �Ϲ� ������ ��� GetAttackPoint() ����
	return IsCritical()
		? Me()->GetAttackPoint()
		* Me()->GetCriticalDamageRate()
		: Me()->GetAttackPoint();
}

int GameManager::CalculateMonsterDamage(Monster* InMonster)
{
	return IsMonsterCritical(InMonster)
		? InMonster->GetAttackPoint()
		* InMonster->GetCriticalDamageRate()
		: InMonster->GetAttackPoint();
}

bool GameManager::IsCritical()
{
	if (PosibilityGenerator(Me()->GetCriticalChance()))
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

void GameManager::LevelUpEvent()
{
	printf("������!!\n");
	Me()->SetLevel(Me()->GetLevel() + 1);
	Me()->SetRequiredExpForLvUp();
	Me()->SetAvailableStat(Me()->GetStatValue());
	HealingPotion->SetPotionLevel(Me()->GetLevel());
	if (Me()->GetLevel() % 10 == 0 && Me()->GetLevel() < 31)
	{
		TakeArtifact(Me()->GetLevel());
	}
}

void GameManager::TakeArtifact(int InLevel)
{
	printf("\n�����մϴ�! ��Ƽ��Ʈ�� ȹ���մϴ�!\n");
	switch (InLevel)
	{
	case 10:
		MainPlayerManager->AddArtifact(Artifact("10���� ���� ��Ƽ��Ʈ", 10));
		break;
	case 20:
		MainPlayerManager->AddArtifact(Artifact("20���� ���� ��Ƽ��Ʈ", 20));
		break;
	case 30:
		MainPlayerManager->AddArtifact(Artifact("30���� ���� ��Ƽ��Ʈ", 30));
		break;
	}
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

void GameManager::ShowEnding()
{
	GameUiManager->ShowEnding(Me());
	EnterVilage();
}
