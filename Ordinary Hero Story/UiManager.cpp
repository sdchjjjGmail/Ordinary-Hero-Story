#include "UiManager.h"
#include "iostream"

using namespace std;

string UiManager::ShowVilageUi()
{
	string Input = "";
	
	while (!IsValidDecision(Input, false))
	{
		printf("----------마을----------\n");
		printf("1. 대장간 방문\n");
		printf("2. 물약 상점 방문\n");
		printf("3. 필드로 이동\n");
		printf("4. 게임 종료\n");
		cin >> Input;
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
		printf("3. 마을로 이동\n");
		printf("4. 게임 종료\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowBlackSmith()
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("----------대장간----------\n");
		printf("1. 무기 강화\n");
		printf("2. 방어구 강화\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowPotionMarket()
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("----------대장간----------\n");
		printf("1. 포션 구매\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowBattleField(Player Player, Monster Monster)
{
	string Input = "";
	
	while (!IsValidDecision(Input, false))
	{
		printf("\n");
		printf("%s\n", Monster.GetName().c_str());
		printf("%d\n", Monster.GetHitPoint());
		printf("%d\n", Monster.GetAttackPoint());
		printf("%d\n", Monster.GetDefencePoint());
		printf("----------------------------\n");
		printf("1. 공격\n");
		printf("2. 도망\n");
		printf("\n");
		cin >> Input;
	}

	return Input;
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
		|| InValue == "5";
}

