#include "UiManager.h"
#include "iostream"

using namespace std;

string UiManager::ShowVilageUi()
{
	string Input = "";
	
	while (!IsValidDecision(Input, false))
	{
		printf("----------����----------\n");
		printf("1. ���尣 �湮\n");
		printf("2. ���� ���� �湮\n");
		printf("3. �ʵ�� �̵�\n");
		printf("4. ���� ����\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowFieldUi()
{
	string Input = "";

	while (!IsValidDecision(Input, true))
	{
		printf("----------�ʵ�----------\n");
		printf("1. �������ͽ�\n");
		printf("2. ���\n");
		printf("3. ������ �̵�\n");
		printf("4. ���� ����\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowBlackSmith()
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("----------���尣----------\n");
		printf("1. ���� ��ȭ\n");
		printf("2. �� ��ȭ\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowPotionMarket()
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("----------���尣----------\n");
		printf("1. ���� ����\n");
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
		printf("1. ����\n");
		printf("2. ����\n");
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

