#include "UiManager.h"
#include "iostream"

using namespace std;

string UiManager::ShowVilageUi(Player* InPlayer)
{
	string Input = "";
	
	while (!IsValidDecision(Input, false))
	{
		printf("----------마을----------\n");
		printf("1. 스테이터스\n");
		printf("2. 스탯 확인\n");
		printf("3. 장비 확인\n");
		printf("4. 대장간 방문\n");
		printf("5. 물약 상점 방문\n");
		printf("6. 초원으로 이동\n");
		if (InPlayer->GetLevel() >= 10)
		{
			printf("7. 숲으로 이동\n");
		}
		if (InPlayer->GetLevel() >= 20)
		{
			printf("8. 늪으로 이동\n");
		}
		if (InPlayer->GetLevel() >= 30)
		{
			printf("9. 보스 도전\n");
		}
		printf("0. 게임 종료\n");
		cin >> Input;

		if (Input == "157")
		{
			// 치트 코드 리턴
			return Input;
		}
	}
	return Input;
}

string UiManager::ShowFieldUi()
{
	string Input = "";

	while (!IsValidDecision(Input, true))
	{
		printf("----------필드----------\n");
		printf("1. 스테이터스\n");
		printf("2. 장비\n");
		printf("3. 스탯 확인\n");
		printf("4. 포션 사용\n");
		printf("5. 마을로 이동\n");
		printf("0. 게임 종료\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowBlackSmith(Weapon* InWeapon, Armor* InArmor)
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("----------대장간----------\n");
		printf("1. 무기 강화(%d 골드)\n", InWeapon->GetRequiredGoldForUpgrade());
		printf("2. 방어구 강화(%d 골드)\n", InArmor->GetRequiredGoldForUpgrade());
		printf("3. 나가기\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowPotionMarket(Potion* InPotion)
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{		
		printf("----------물약 상점----------\n");
		printf("1. 포션 구매(%d 골드)\n", InPotion->GetPrice());
		printf("2. 나가기\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowBattleField(Monster* InMonster)
{
	string Input = "";
	
	while (!IsValidDecision(Input, false))
	{
		printf("\n");
		printf("%s\n", InMonster->GetName().c_str());
		printf("유효하지 않은 값 입력 시 자동으로 공격합니다.\n");
		printf("----------------------------\n");
		printf("1. 공격\n");
		printf("2. 도망\n");
		printf("\n");
		cin >> Input;
	}

	return Input;
}

void UiManager::ShowMonsterStatus(Monster* InMonster)
{
	printf("Level : %d\n", InMonster->GetLevel());
	printf("남은 체력 : %d\n", InMonster->GetHitPoint());
	printf("공격력 : %d\n", InMonster->GetAttackPoint());
	printf("방어력 : %d\n", InMonster->GetDefencePoint());
	printf("속도 : %d\n", InMonster->GetSpeed());
	printf("크리티컬 확률 : %d퍼센트\n", InMonster->GetCriticalChance());
	printf("크리티컬 데미지 : %d배\n", InMonster->GetCriticalDamageRate());
}

void UiManager::ShowStatus(Player* InPlayer)
{
	printf("\n**Player Info**\n");
	printf("Level : %d\n", InPlayer->GetLevel());
	printf("체력 : %d/%d\n", InPlayer->GetHitPoint(), InPlayer->GetFullHitPoint());
	printf("공격력 : %d\n", InPlayer->GetAttackPoint());
	printf("방어력 : %d\n", InPlayer->GetDefencePoint());
	printf("속도 : %d\n", InPlayer->GetSpeed());
	printf("크리티컬 확률 : %d퍼센트\n", InPlayer->GetCriticalChance());
	printf("크리티컬 데미지 : %d배\n", InPlayer->GetCriticalDamageRate());
	printf("골드 : %d\n", InPlayer->GetMyGold());
	printf("Exp : %d/%d\n", InPlayer->GetExp(), InPlayer->GetRequiredExpForLvUp());
	printf("\n");
}

string UiManager::ShowStatPoints(Player* InPlayer)
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("\n**Player Stat Points**\n");
		printf("1. 체력 : +%d\n", InPlayer->GetHitPointStat());
		printf("2. 공격력 : +%d\n", InPlayer->GetAttackPointStat());
		printf("3. 방어력 : +%d\n", InPlayer->GetDefencePointStat());
		printf("4. 속도 : +%d\n", InPlayer->GetSpeedStat());
		printf("5. 크리티컬 확률 : +%d\n", InPlayer->GetCriticalChanceStat());
		printf("스탯포인트 : %d\n", InPlayer->GetAvailableStat());
		printf("올리고 싶은 능력치를 선택해 주세요 : ");
		cin >> Input;
	}
	return Input;
}

void UiManager::ShowWearings(Player* InPlayer)
{
	printf("\nWeapon Info\n");
	printf("Upgraded : %d\n", InPlayer->GetPlayerWeapon()->GetUpgradeLevel());
	printf("AP : %d\n", InPlayer->GetPlayerWeapon()->GetAttackPoint());
	printf("Gold For Upgrade : %d\n", InPlayer->GetPlayerWeapon()->GetRequiredGoldForUpgrade());

	printf("\nArmor Info\n");
	printf("Upgraded : %d\n", InPlayer->GetPlayerArmor()->GetUpgradeLevel());
	printf("DP : %d\n", InPlayer->GetPlayerArmor()->GetDefencePoint());
	printf("Gold For Upgrade : %d\n", InPlayer->GetPlayerArmor()->GetRequiredGoldForUpgrade());
}



bool UiManager::IsValidDecision(string InValue, bool IsField)
{
	if (IsField && (InValue == "d" || InValue == "D"))
	{
		return true;
	}
	return InValue == "1" 
		|| InValue == "2" 
		|| InValue == "3" 
		|| InValue == "4" 
		|| InValue == "5"
		|| InValue == "6"
		|| InValue == "7"
		|| InValue == "8"
		|| InValue == "9"
		|| InValue == "0";
}
