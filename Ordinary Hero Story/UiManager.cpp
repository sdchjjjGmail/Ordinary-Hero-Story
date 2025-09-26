#include "UiManager.h"
#include "iostream"

using namespace std;

string UiManager::ShowVilageUi(Player* InPlayer)
{
	string Input = "";
	
	while (!IsValidDecision(Input, false))
	{
		printf("----------����----------\n");
		printf("1. �������ͽ�\n");
		printf("2. ���� Ȯ��\n");
		printf("3. ��� Ȯ��\n");
		printf("4. ���尣 �湮\n");
		printf("5. ���� ���� �湮\n");
		printf("6. �ʿ����� �̵�\n");
		if (InPlayer->GetLevel() >= 10)
		{
			printf("7. ������ �̵�\n");
		}
		if (InPlayer->GetLevel() >= 20)
		{
			printf("8. ������ �̵�\n");
		}
		if (InPlayer->GetLevel() >= 30)
		{
			printf("9. ���� ����\n");
		}
		printf("0. ���� ����\n");
		cin >> Input;

		if (Input == "157")
		{
			// ġƮ �ڵ� ����
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
		printf("----------�ʵ�----------\n");
		printf("1. �������ͽ�\n");
		printf("2. ���\n");
		printf("3. ���� Ȯ��\n");
		printf("4. ���� ���\n");
		printf("5. ������ �̵�\n");
		printf("0. ���� ����\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowBlackSmith(Weapon* InWeapon, Armor* InArmor)
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("----------���尣----------\n");
		printf("1. ���� ��ȭ(%d ���)\n", InWeapon->GetRequiredGoldForUpgrade());
		printf("2. �� ��ȭ(%d ���)\n", InArmor->GetRequiredGoldForUpgrade());
		printf("3. ������\n");
		cin >> Input;
	}
	return Input;
}

string UiManager::ShowPotionMarket(Potion* InPotion)
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{		
		printf("----------���� ����----------\n");
		printf("1. ���� ����(%d ���)\n", InPotion->GetPrice());
		printf("2. ������\n");
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
		printf("��ȿ���� ���� �� �Է� �� �ڵ����� �����մϴ�.\n");
		printf("----------------------------\n");
		printf("1. ����\n");
		printf("2. ����\n");
		printf("\n");
		cin >> Input;
	}

	return Input;
}

void UiManager::ShowMonsterStatus(Monster* InMonster)
{
	printf("Level : %d\n", InMonster->GetLevel());
	printf("���� ü�� : %d\n", InMonster->GetHitPoint());
	printf("���ݷ� : %d\n", InMonster->GetAttackPoint());
	printf("���� : %d\n", InMonster->GetDefencePoint());
	printf("�ӵ� : %d\n", InMonster->GetSpeed());
	printf("ũ��Ƽ�� Ȯ�� : %d�ۼ�Ʈ\n", InMonster->GetCriticalChance());
	printf("ũ��Ƽ�� ������ : %d��\n", InMonster->GetCriticalDamageRate());
}

void UiManager::ShowStatus(Player* InPlayer)
{
	printf("\n**Player Info**\n");
	printf("Level : %d\n", InPlayer->GetLevel());
	printf("ü�� : %d/%d\n", InPlayer->GetHitPoint(), InPlayer->GetFullHitPoint());
	printf("���ݷ� : %d\n", InPlayer->GetAttackPoint());
	printf("���� : %d\n", InPlayer->GetDefencePoint());
	printf("�ӵ� : %d\n", InPlayer->GetSpeed());
	printf("ũ��Ƽ�� Ȯ�� : %d�ۼ�Ʈ\n", InPlayer->GetCriticalChance());
	printf("ũ��Ƽ�� ������ : %d��\n", InPlayer->GetCriticalDamageRate());
	printf("��� : %d\n", InPlayer->GetMyGold());
	printf("Exp : %d/%d\n", InPlayer->GetExp(), InPlayer->GetRequiredExpForLvUp());
	printf("\n");
}

string UiManager::ShowStatPoints(Player* InPlayer)
{
	string Input = "";

	while (!IsValidDecision(Input, false))
	{
		printf("\n**Player Stat Points**\n");
		printf("1. ü�� : +%d\n", InPlayer->GetHitPointStat());
		printf("2. ���ݷ� : +%d\n", InPlayer->GetAttackPointStat());
		printf("3. ���� : +%d\n", InPlayer->GetDefencePointStat());
		printf("4. �ӵ� : +%d\n", InPlayer->GetSpeedStat());
		printf("5. ũ��Ƽ�� Ȯ�� : +%d\n", InPlayer->GetCriticalChanceStat());
		printf("��������Ʈ : %d\n", InPlayer->GetAvailableStat());
		printf("�ø��� ���� �ɷ�ġ�� ������ �ּ��� : ");
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
