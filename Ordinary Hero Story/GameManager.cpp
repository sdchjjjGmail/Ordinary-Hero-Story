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
			// 스테이터스 확인
			GameUiManager->ShowStatus(Me());
			break;
		case 2:
			// 스탯포인트 확인 및 사용
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(Me())));
			break;
		case 3:
			// 장비 확인
			GameUiManager->ShowWearings(Me(), HealingPotion);
			break;
		case 4:
			// 대장간 입장 및 장비 강화
			MoveToBlackSmith(stoi(GameUiManager->ShowBlackSmith(
				Me()->GetPlayerWeapon(), Me()->GetPlayerArmor())));
			break;
		case 5:
			// 물약 상점 입장 및 물약 구매
			MoveToPotionMarket(stoi(GameUiManager->ShowPotionMarket(HealingPotion)));
			break;
		case 6:
			// 필드로 이동
			GameMapManager->SetCurrentMap(Field::Field1);
			Out = true;
			break;
		case 7:
			// 필드로 이동
			GameMapManager->SetCurrentMap(Field::Field2);
			Out = true;
			break;
		case 8:
			// 필드로 이동
			GameMapManager->SetCurrentMap(Field::Field3);
			Out = true;
			break;
		case 9:
			// 보스로 이동
			GameMapManager->SetCurrentMap(Field::BossField);
			Out = true;
			break;
		case 0:
			// 게임 종료
			Out = true;
			GameEnd = true;
			break;
		case 157:
			// 테스트용 치트 모드 플래그
			GameTester Tester;
			Tester.SetCheat(Me());
			break;
		default:
			// 그 외 입력 불가
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
			printf("골드가 부족합니다!");
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
			printf("골드가 부족합니다!");
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
		printf("구매할 양을 입력하세요.\n");
		cin >> Amount;
		if (Amount < 0)
		{
			printf("정상적인 양을 입력하세요.\n");
		}
		else if (HealingPotion->GetPrice() * Amount > Me()->GetMyGold())
		{
			printf("골드가 부족합니다..\n");
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
	printf("\n필드에 입장했습니다!\n");
	printf("d 키를 입력하여 앞으로 이동하세요.\n");

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
			// 스테이터스 확인
			GameUiManager->ShowStatus(Me());
			break;
		case 2:
			// 장비 확인
			GameUiManager->ShowWearings(Me(), HealingPotion);
			break;
		case 3:
			// 스탯포인트 확인 및 사용
			IncreaseStat(stoi(GameUiManager->ShowStatPoints(Me())));
			break;
		case 4:
			// 포션 사용
			if (Me()->GetHitPoint() == Me()->GetFullHitPoint())
			{
				printf("체력이 가득 차있습니다.\n");
				break;
			}
			MainPlayerManager->UsePotion(HealingPotion);
			break;
		case 5:
			// 마을로 이동
			Out = true;
			break;
		case 0:
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
	if (InType == 0)
	{
		return;
	}
	if (InType < 0 || InType > 5)
	{
		printf("\n유효하지 않은 스탯 선택입니다.\n\n");
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
		printf("스탯 값을 입력해 주세요(0 입력 시 취소.) : ");
		cin >> Value;

		if (Value > Me()->GetAvailableStat())
		{
			printf("스탯이 부족합니다.\n");
			continue;
		}
		else if (Value < 0)
		{
			printf("정상적인 값을 입력해 주세요.\n");
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
	printf("\n앞으로 이동!\n");
	if (EncounterMonster())
	{
		printf("\n몬스터와 마주쳤습니다!\n");
		Monster* CreatedMonster = EncounterMonsterManager->CreateMonster(Me(), GameMapManager->GetCurrentMap());
		StartBattle(CreatedMonster);
	}
}

void GameManager::StartBattle(Monster* InMonster)
{
	printf("전투 시작\n");
	GameUiManager->ShowMonsterStatus(InMonster);
	bool BattleFinish = false;
	int Turn = 1;
	GameTester Tester;

	while (!BattleFinish)
	{
		if (InMonster->GetHitPoint() <= 0)
		{
			printf("\n승리!!\n");

			printf("%d만큼의 경험치를 얻었다!\n", InMonster->GetDropExp());
			printf("%d만큼의 골드를 얻었다!\n", InMonster->GetDropGold());

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

			printf("패배..\n");
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
	// 속도가 동일할 경우 플레이어 선공
	if (PlayerSpeed == MonsterSpeed)
	{
		return 1;
	}
	
	printf("\nPlayerSpeed : %d, MonsterSpeed : %d\n", PlayerSpeed, MonsterSpeed);
	if (PlayerSpeed > MonsterSpeed)
	{
		if (InTurn % 3 == 0)
		{
			// 턴이 3의 배수일 경우 속도가 느린 쪽이 선공
			return 2;
		}
		return 1;
	}
	else
	{
		if (InTurn % 3 == 0)
		{
			// 턴이 3의 배수일 경우 속도가 느린 쪽이 선공
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
	printf("\n%s의 공격!\n", InMonster->GetName().c_str());
	InMonster->Attack(Me(), CalculateMonsterDamage(InMonster));
}

int GameManager::CalculateDamage()
{
	// 크리티컬 공격일 경우 GetAttackPoint() * GetCriticalDamageRate() 리턴
	// 일반 공격일 경우 GetAttackPoint() 리턴
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
	printf("레벨업!!\n");
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
	printf("\n축하합니다! 아티팩트를 획득합니다!\n");
	switch (InLevel)
	{
	case 10:
		MainPlayerManager->AddArtifact(Artifact("10레벨 축하 아티팩트", 10));
		break;
	case 20:
		MainPlayerManager->AddArtifact(Artifact("20레벨 축하 아티팩트", 20));
		break;
	case 30:
		MainPlayerManager->AddArtifact(Artifact("30레벨 축하 아티팩트", 30));
		break;
	}
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

void GameManager::ShowEnding()
{
	GameUiManager->ShowEnding(Me());
	EnterVilage();
}
